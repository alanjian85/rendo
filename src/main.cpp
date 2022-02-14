#include <iostream>
#include <optional>

#include "camera.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "model.hpp"
#include "utility.hpp"
using namespace box;

class head_shader : public basic_shader {
public:
    head_shader(matrix4 proj, matrix4 view, vector3 cam_pos, const sampler_cube& sampler) 
        : sampler_(sampler)
    {
        proj_ = proj;
        view_ = view;
        cam_pos_ = cam_pos;
        head_.load("assets/models/african_head.obj");
    }

    virtual vector4 vert(int n) override {
        auto pos = vector4(head_.get_vertex(n), 1);
        v_pos[n % 3] = vector3(pos);
        v_normal[n % 3] = head_.get_normal(n);
        return proj_ * view_ * pos;
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto pos = frag_lerp(v_pos, bar);
        auto normal = frag_lerp(v_normal, bar).normalize();
        auto cam_dir = (pos - cam_pos_).normalize();
        auto color = sampler_(reflect(cam_dir, normal));
        if (color.a < 0.1)
            return std::nullopt;
        return color;
    }

    void render(renderer& r) {
        r.render(head_.num_vertices(), *this);
    }
private:
    matrix4 proj_;
    matrix4 view_;

    vector3 cam_pos_;
    const sampler_cube& sampler_;

    model head_;
    vector3 v_pos[3];
    vector3 v_normal[3];
};

class skybox_shader : public basic_shader {
public:
    skybox_shader(matrix4 proj, matrix4 view, const sampler_cube& sampler) 
        : sampler_(sampler)
    {
        proj_ = proj;
        view_ = matrix4(matrix3(view));
        cube_.load("assets/models/cube.obj");
    }

    virtual vector4 vert(int n) override {
        auto pos = vector4(cube_.get_vertex(n), 1);
        v_pos[n % 3] = vector3(pos);
        return proj_ * view_ * pos;
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto pos = frag_lerp(v_pos, bar);
        return sampler_(pos);
    }

    void render(renderer& r) {
        r.render(cube_.num_vertices(), *this);
    }
private:
    matrix4 proj_;
    matrix4 view_;

    const sampler_cube& sampler_;

    model cube_;
    vector3 v_pos[3];
};

int main() {
    try {
        framebuffer fb(1024, 1024);
        fb.clear({1, 0, 0, 1.0});
        renderer r(fb);

        camera cam;
        cam.yaw = -110;
        cam.pitch = -30;
        cam.pos.z = 3;

        cubemap skybox;
        skybox.load("assets/textures/skybox");

        skybox_shader ss(cam.proj(fb.aspect()), cam.view(), skybox.sampler);
        r.disable_depth_write();
        ss.render(r);

        head_shader hs(cam.proj(fb.aspect()), cam.view(), cam.pos, skybox.sampler);
        r.enable_depth_write();
        //hs.render(r);

        fb.write("image.ppm");
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}