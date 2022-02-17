#include <iostream>
#include <optional>

#include "camera.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "model.hpp"
#include "light.hpp"
#include "utility.hpp"
using namespace box;

class head_shader : public basic_shader {
public:
    head_shader(matrix4 proj, matrix4 view, vector3 cam_pos, const sampler_cube& sampler) 
    {
        proj_ = proj;
        view_ = view;
        cam_pos_ = cam_pos;
        light_.pos = vector3(1.2, 1.0, 2.0);
        light_.ambient = color_rgb(0.2);
        light_.diffuse = color_rgb(0.5);
        light_.specular = color_rgb(1.0);
        light_.constant = 1;
        light_.linear = 0.09;
        light_.quadratic = 0.032;
        head_.load("assets/models/african_head.obj");
    }

    virtual vector4 vert(int n) override {
        auto pos = vector4(head_.get_vertex(n), 1);
        mat_ = head_.get_mat(n);
        v_pos_[n % 3] = vector3(pos);
        v_normal_[n % 3] = head_.get_normal(n);
        v_uv_[n % 3] = head_.get_uv(n);
        sampler_.bind_texture(mat_->diffuse_map);
        return proj_ * view_ * pos;
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto pos = frag_lerp(v_pos_, bar);
        auto normal = frag_lerp(v_normal_, bar).normalize();
        auto uv = frag_lerp(v_uv_, bar);

        auto cam_dir = (pos - cam_pos_).normalize();
        auto light_dir = (light_.pos - pos).normalize();
        auto halfway_dir = (cam_dir + light_dir).normalize();
        
        auto distance = (cam_pos_ - pos).length();
        auto attenuation = light_.constant + distance * light_.linear + distance * distance * light_.quadratic;

        auto ambient = light_.ambient * color_rgb(sampler_(uv));
        auto diffuse = light_.diffuse * color_rgb(sampler_(uv)) * mat_->diffuse * color_rgb(std::max(dot(light_dir, normal), 0.0));
        auto specular = light_.specular * mat_->specular * color_rgb(std::pow(std::max(dot(halfway_dir, normal), 0.0), mat_->shininess));

        diffuse *= attenuation;
        specular *= attenuation;

        auto color = color_rgba(ambient + diffuse + specular, 1);
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

    point_light light_;

    sampler2 sampler_;
    model head_;
    vector3 v_pos_[3];
    vector3 v_normal_[3];
    vector2 v_uv_[3];
    const material* mat_;
};

int main() {
    try {
        framebuffer fb(1024, 1024);
        fb.clear({1, 0, 0, 1.0});
        renderer r(fb);

        camera cam;
        cam.pos.x = 3;
        cam.pos.z = 3;
        cam.pos.y = -1;
        cam.yaw = -135;
        cam.pitch = 15;

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