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

class depth_shader : public basic_shader {
public:
    depth_shader(matrix4 mvp, const model& mesh) {
        mvp_ = mvp;
        mesh_ = &mesh;
    }

    virtual vector4 vert(int n) override {
        auto pos = mesh_->get_vertex(n);
        return mvp_ * vector4(pos, 1);
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        return color_rgba(0, 0, 0, 1);
    }
private:
    matrix4 mvp_;
    const model* mesh_;
};

class model_shader : public basic_shader {
public:
    model_shader(matrix4 mvp, vector3 cam_pos, const model& mesh, texture shadowmap, directional_light light, matrix4 light_mvp) 
    {
        mvp_ = mvp;
        cam_pos_ = cam_pos;
        mesh_ = &mesh;
        shadowmap_ = std::move(shadowmap);
        shadowmap_sampler_.bind_texture(shadowmap_);
        light_ = light;
        light_mvp_ = light_mvp;
    }

    virtual vector4 vert(int n) override {
        auto pos = mesh_->get_vertex(n);
        mat_ = mesh_->get_mat(n);
        v_pos_[n % 3] = vector3(pos);
        v_normal_[n % 3] = mesh_->get_normal(n);
        v_uv_[n % 3] = mesh_->get_uv(n);
        diffuse_sampler_.bind_texture(mat_->diffuse_map);
        specular_sampler_.bind_texture(mat_->specular_map);
        normal_sampler_.bind_texture(mat_->normal_map);
        return mvp_ * vector4(pos, 1);
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

        v_tbn_[0](0, 0) = tangent.x; v_tbn_[0](0, 1) = bitangent.x; v_tbn_[0](0, 2) = v_normal_[0].x;
        v_tbn_[0](1, 0) = tangent.y; v_tbn_[0](1, 1) = bitangent.y; v_tbn_[0](1, 2) = v_normal_[0].y;
        v_tbn_[0](2, 0) = tangent.z; v_tbn_[0](2, 1) = bitangent.z; v_tbn_[0](2, 2) = v_normal_[0].z;
    
        v_tbn_[1](0, 0) = tangent.x; v_tbn_[1](0, 1) = bitangent.x; v_tbn_[1](0, 2) = v_normal_[1].x;
        v_tbn_[1](1, 0) = tangent.y; v_tbn_[1](1, 1) = bitangent.y; v_tbn_[1](1, 2) = v_normal_[1].y;
        v_tbn_[1](2, 0) = tangent.z; v_tbn_[1](2, 1) = bitangent.z; v_tbn_[1](2, 2) = v_normal_[1].z;

        v_tbn_[2](0, 0) = tangent.x; v_tbn_[2](0, 1) = bitangent.x; v_tbn_[2](0, 2) = v_normal_[2].x;
        v_tbn_[2](1, 0) = tangent.y; v_tbn_[2](1, 1) = bitangent.y; v_tbn_[2](1, 2) = v_normal_[2].y;
        v_tbn_[2](2, 0) = tangent.z; v_tbn_[2](2, 1) = bitangent.z; v_tbn_[2](2, 2) = v_normal_[2].z;
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto pos = frag_lerp(v_pos_, bar);
        auto f_normal = frag_lerp(v_normal_, bar).normalize();
        auto uv = frag_lerp(v_uv_, bar);
        auto tbn = frag_lerp(v_tbn_, bar);

        auto cam_dir = (pos - cam_pos_).normalize();
        auto light_dir = light_.dir.normalize();
        auto halfway_dir = (cam_dir + light_dir).normalize();

        auto pos_light_space = light_mvp_ * vector4(pos, 1);
        auto pos_proj_coord = vector3(pos_light_space) / pos_light_space.w;
        pos_proj_coord = pos_proj_coord * 0.5 + 0.5;
        auto current_depth = pos_proj_coord.z;
        auto bias = 0.005;
        auto shadow = 0.0;
        auto texel_size = vector2(1.0 / shadowmap_.width(), 1.0 / shadowmap_.height());
        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                auto depth = shadowmap_sampler_(vector2(pos_proj_coord) + vector2(x, y) * texel_size).r;
                shadow += current_depth - bias > depth ? 1.0 : 0.0;
            }
        }
        shadow /= 9;

        auto normal = (tbn * vector3(normal_sampler_(uv))).normalize();

        auto ambient = light_.ambient * color_rgb(diffuse_sampler_(uv));
        auto diffuse = light_.diffuse * color_rgb(diffuse_sampler_(uv)) * mat_->diffuse * color_rgb(std::max(dot(light_dir, normal), 0.0));
        auto specular = light_.specular * color_rgb(specular_sampler_(uv)) * mat_->specular * color_rgb(std::pow(std::max(dot(halfway_dir, normal), 0.0), mat_->shininess));

        auto color = color_rgba(ambient + (1 - shadow) * (diffuse + specular), 1);
        if (color.a < 0.1)
            return std::nullopt;
        return color;
    }
private:
    matrix4 mvp_;
    vector3 cam_pos_;
    const model* mesh_;

    directional_light light_;
    matrix4 light_mvp_;

    texture shadowmap_;
    sampler2 shadowmap_sampler_;
    sampler2 diffuse_sampler_;
    sampler2 specular_sampler_;
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
        renderer r;

        camera cam;
        cam.pos.x = 0;
        cam.pos.y = 0.65;
        cam.pos.z = 2;
        cam.yaw = -90;
        cam.pitch = -15;

        model diablo;
        diablo.load("assets/models/diablo3_pose.obj");

        directional_light light;
        light.dir = vector3(0, 0.65, 2);
        light.ambient = color_rgb(0.1);
        light.diffuse = color_rgb(1.0);
        light.specular = color_rgb(0.5);

        framebuffer shadowmap(1024, 1024);
        framebuffer fb(1024, 1024);

        auto light_mvp = light.proj(0) * light.view();
        shadowmap.clear({0, 0, 0, 0});
        depth_shader ds(light_mvp, diablo);
        r.bind_framebuffer(shadowmap);
        r.set_face_culling(cull_type::front);
        r.render(diablo.num_vertices(), ds);

        auto mvp = cam.proj(fb.aspect()) * cam.view();
        fb.clear({0, 0, 0, 0});
        model_shader ms(mvp, cam.pos, diablo, shadowmap.zbuffer(), light, light_mvp);
        r.bind_framebuffer(fb);
        r.set_face_culling(cull_type::back);
        r.render(diablo.num_vertices(), ms);

        fb.write("image.pam");
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}