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
        v_uv[n % 3] = head_.get_uv(n);
        sampler_.bind_texture(head_.get_mat(n)->diffuse_map);
        return proj_ * view_ * pos;
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto pos = frag_lerp(v_pos, bar);
        auto normal = frag_lerp(v_normal, bar).normalize();
        auto uv = frag_lerp(v_uv, bar);
        auto cam_dir = (pos - cam_pos_).normalize();
        auto color = sampler_(uv);
        if (color.a < 0.1)
            return std::nullopt;
        return color;
    }

    void render(renderer& r) {
        r.render(head_.num_vertices(), *this);
    }
private:
    vector3 cam_pos_;
    matrix4 proj_;
    matrix4 view_;

    sampler2 sampler_;
    model head_;
    vector3 v_pos[3];
    vector3 v_normal[3];
    vector2 v_uv[3];
};

int main() {
    try {
        framebuffer fb(1024, 1024);
        fb.clear({1, 0, 0, 1.0});
        renderer r(fb);

        camera cam;
        cam.pos.z = 3;

        cubemap skybox;
        skybox.load("assets/textures/skybox");

        head_shader hs(cam.proj(fb.aspect()), cam.view(), cam.pos, skybox.sampler);
        hs.render(r);

        fb.write("image.pam");
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}