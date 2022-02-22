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
        head_.load("assets/models/DamagedHelmet.obj");
    }

    virtual vector4 vert(int n) override {
        auto pos = vector4(head_.get_vertex(n), 1);
        mat_ = head_.get_mat(n);
        v_pos_[n % 3] = vector3(pos);
        v_normal_[n % 3] = head_.get_normal(n);
        v_uv_[n % 3] = head_.get_uv(n);
        ambient_sampler_.bind_texture(mat_->ambient_map);
        diffuse_sampler_.bind_texture(mat_->diffuse_map);
        normal_sampler_.bind_texture(mat_->normal_map);
        return proj_ * view_ * pos;
    }

    virtual void geometry() {
        auto edge1 = v_pos_[1] - v_pos_[0];
        auto edge2 = v_pos_[2] - v_pos_[0];
        auto duv1 = v_uv_[1] - v_uv_[0];
        auto duv2 = v_uv_[2] - v_uv_[0];

        auto f = 1.0 / (duv1.x * duv2.y - duv2.x * duv1.y);
        vector3 tangent;
        tangent.x = f * (duv2.y * edge1.x - duv1.y * edge2.x);
        tangent.y = f * (duv2.y * edge1.y - duv1.y * edge2.y);
        tangent.z = f * (duv2.y * edge1.z - duv1.y * edge2.z);
        tangent = tangent.normalize();
        vector3 bitangent;
        bitangent.x = f * (-duv2.x * edge1.x + duv1.x * edge2.x);
        bitangent.y = f * (-duv2.x * edge1.y + duv1.x * edge2.y);
        bitangent.z = f * (-duv2.x * edge1.z + duv1.x * edge2.z);
        bitangent = bitangent.normalize();

        v_tbn_[0](0, 0) = tangent.x;      v_tbn_[0](0, 1) = tangent.y;      v_tbn_[0](0, 2) = tangent.z;
        v_tbn_[0](1, 0) = bitangent.x;    v_tbn_[0](0, 1) = bitangent.y;    v_tbn_[0](0, 2) = bitangent.z;
        v_tbn_[0](2, 0) = v_normal_[0].x; v_tbn_[0](0, 1) = v_normal_[0].y; v_tbn_[0](0, 2) = v_normal_[0].z;
    
        v_tbn_[1](0, 0) = tangent.x;      v_tbn_[1](0, 1) = tangent.y;      v_tbn_[1](0, 2) = tangent.z;
        v_tbn_[1](1, 0) = bitangent.x;    v_tbn_[1](0, 1) = bitangent.y;    v_tbn_[1](0, 2) = bitangent.z;
        v_tbn_[1](2, 0) = v_normal_[1].x; v_tbn_[1](0, 1) = v_normal_[1].y; v_tbn_[1](0, 2) = v_normal_[1].z;

        v_tbn_[2](0, 0) = tangent.x;      v_tbn_[2](0, 1) = tangent.y;      v_tbn_[2](0, 2) = tangent.z;
        v_tbn_[2](1, 0) = bitangent.x;    v_tbn_[2](0, 1) = bitangent.y;    v_tbn_[2](0, 2) = bitangent.z;
        v_tbn_[2](2, 0) = v_normal_[2].x; v_tbn_[2](0, 1) = v_normal_[2].y; v_tbn_[2](0, 2) = v_normal_[2].z;
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto pos = frag_lerp(v_pos_, bar);
        auto f_normal = frag_lerp(v_normal_, bar).normalize();
        auto uv = frag_lerp(v_uv_, bar);
        auto tbn = frag_lerp(v_tbn_, bar);

        auto cam_dir = (pos - cam_pos_).normalize();
        auto light_dir = (light_.pos - pos).normalize();
        auto halfway_dir = (cam_dir + light_dir).normalize();
        
        auto distance = (cam_pos_ - pos).length();
        auto attenuation = light_.constant + distance * light_.linear + distance * distance * light_.quadratic;

        auto normal = tbn * vector3(normal_sampler_(uv));

        auto ambient = light_.ambient * color_rgb(ambient_sampler_(uv));
        auto diffuse = light_.diffuse * color_rgb(diffuse_sampler_(uv)) * mat_->diffuse * color_rgb(std::max(dot(light_dir, normal), 0.0));
        auto specular = light_.specular * mat_->specular * color_rgb(std::pow(std::max(dot(halfway_dir, normal), 0.0), mat_->shininess));

        diffuse *= attenuation;
        specular *= attenuation;

        auto intensity = std::max(dot(light_dir, normal), 0.0);
        if (intensity > 0.85) intensity = 1;
        else if (intensity > 0.60) intensity = 0.80;
        else if (intensity > 0.45) intensity = 0.60;
        else if (intensity > 0.30) intensity = 0.45;
        else if (intensity > 0.15) intensity = 0.30;
        else intensity = 0;

        auto color = color_rgba((ambient + diffuse + specular) * intensity, 1);
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

    sampler2 ambient_sampler_;
    sampler2 diffuse_sampler_;
    sampler2 normal_sampler_;
    model head_;
    vector3 v_pos_[3];
    vector3 v_normal_[3];
    vector2 v_uv_[3];
    matrix3 v_tbn_[3];
    const material* mat_;
};

int main() {
    try {
        framebuffer fb(1024, 1024);
        fb.clear({1, 0, 0, 1.0});
        renderer r(fb);

        camera cam;
        cam.pos.x = 2;
        cam.pos.z = 2;
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