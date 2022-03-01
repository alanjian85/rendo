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

class position_shader : public basic_shader {
public:
    position_shader(matrix4 mvp, const model& mesh) {
        mvp_ = mvp;
        mesh_ = &mesh;
    }

    virtual vector4 vert(int n) override {
        auto pos = mesh_->get_vertex(n);
        v_pos_[n % 3] = pos;
        return mvp_ * vector4(pos, 1);
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto pos = frag_lerp(v_pos_, bar);
        return color_rgba(pos.x, pos.y, pos.z, 1);
    }
private:
    matrix4 mvp_;
    const model* mesh_;
    vector3 v_pos_[3];
};

class normal_shader : public basic_shader {
public:
    normal_shader(matrix4 mvp, const model& mesh) {
        mvp_ = mvp;
        mesh_ = &mesh;
    }

    virtual vector4 vert(int n) override {
        auto pos = mesh_->get_vertex(n);
        v_pos_[n % 3] = pos;
        v_uv_[n % 3] = mesh_->get_uv(n);
        v_normal_[n % 3] = mesh_->get_normal(n);
        normal_sampler_.bind_texture(mesh_->get_mat(n)->normal_map);
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
        auto tbn = frag_lerp(v_tbn_, bar);
        auto uv = frag_lerp(v_uv_, bar);
        auto normal = (tbn * vector3(normal_sampler_(uv))).normalize();
        return color_rgba(normal.x, normal.y, normal.z, 1);
    }
private:
    matrix4 mvp_;
    const model* mesh_;
    vector3 v_pos_[3];
    vector2 v_uv_[3];
    vector3 v_normal_[3];
    matrix3 v_tbn_[3];
    sampler2 normal_sampler_;
};

class diffuse_shader : public basic_shader {
public:
    diffuse_shader(matrix4 mvp, const model& mesh) {
        mvp_ = mvp;
        mesh_ = &mesh;
    }

    virtual vector4 vert(int n) override {
        auto pos = mesh_->get_vertex(n);
        v_uv_[n % 3] = mesh_->get_uv(n);
        diffuse_sampler_.bind_texture(mesh_->get_mat(n)->diffuse_map);
        return mvp_ * vector4(pos, 1);
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto uv = frag_lerp(v_uv_, bar);
        return diffuse_sampler_(uv);
    }
private:
    matrix4 mvp_;
    const model* mesh_;
    vector2 v_uv_[3];
    sampler2 diffuse_sampler_;
};

class specular_shader : public basic_shader {
public:
    specular_shader(matrix4 mvp, const model& mesh) {
        mvp_ = mvp;
        mesh_ = &mesh;
    }

    virtual vector4 vert(int n) override {
        auto pos = mesh_->get_vertex(n);
        v_uv_[n % 3] = mesh_->get_uv(n);
        specular_sampler_.bind_texture(mesh_->get_mat(n)->specular_map);
        return mvp_ * vector4(pos, 1);
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto uv = frag_lerp(v_uv_, bar);
        return specular_sampler_(uv);
    }
private:
    matrix4 mvp_;
    const model* mesh_;
    vector2 v_uv_[3];
    sampler2 specular_sampler_;
};

class emission_shader : public basic_shader {
public:
    emission_shader(matrix4 mvp, const model& mesh) {
        mvp_ = mvp;
        mesh_ = &mesh;
    }

    virtual vector4 vert(int n) override {
        auto pos = mesh_->get_vertex(n);
        v_uv_[n % 3] = mesh_->get_uv(n);
        emission_sampler_.bind_texture(mesh_->get_mat(n)->emission_map);
        return mvp_ * vector4(pos, 1);
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto uv = frag_lerp(v_uv_, bar);
        return emission_sampler_(uv);
    }
private:
    matrix4 mvp_;
    const model* mesh_;
    vector2 v_uv_[3];
    sampler2 emission_sampler_;
};

class bright_shader : public basic_shader {
public:
    bright_shader(const model& mesh, texture color_buffer) 
        : mesh_(&mesh)
    {
        color_buffer_ = std::move(color_buffer);
        color_buffer_sampler_.bind_texture(color_buffer_);
    }

    virtual vector4 vert(int n) override {
        auto pos = mesh_->get_vertex(n);
        v_uv_[n % 3] = mesh_->get_uv(n);
        return vector4(pos, 1);
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto uv = frag_lerp(v_uv_, bar);

        auto color = color_buffer_sampler_(uv);
        auto brightness = dot(vector3(color), vector3(0.2126, 0.7152, 0.0722));
        if (brightness > 1)
            return color_rgba(color, 1);
        else
            return color_rgba(0, 0, 0, 1);
    }
private:
    const model* mesh_;
    texture color_buffer_;
    sampler2 color_buffer_sampler_;
    vector2 v_uv_[3];
};

class blur_shader : public basic_shader {
public:
    blur_shader(const model& mesh, texture color_buffer, bool horizontal) 
        : mesh_(&mesh)
    {
        color_buffer_ = std::move(color_buffer);
        color_buffer_sampler_.bind_texture(color_buffer_);
        horizontal_ = horizontal;
    }

    virtual vector4 vert(int n) override {
        auto pos = mesh_->get_vertex(n);
        v_uv_[n % 3] = mesh_->get_uv(n);
        return vector4(pos, 1);
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {        
        double weight[5] = {0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216};

        auto uv = frag_lerp(v_uv_, bar);
        auto tex_offset = 1.0 / vector2(color_buffer_.width(), color_buffer_.height());
        auto result = color_rgb(color_buffer_sampler_(uv)) * weight[0];
        if (horizontal_) {
            for (int i = 1; i < 5; ++i) {
                result += color_rgb(color_buffer_sampler_(uv + vector2(tex_offset.x * i, 0))) * weight[i];
                result += color_rgb(color_buffer_sampler_(uv - vector2(tex_offset.x * i, 0))) * weight[i];
            }
        } else {
            for (int i = 1; i < 5; ++i) {
                result += color_rgb(color_buffer_sampler_(uv + vector2(0, tex_offset.y * i))) * weight[i];
                result += color_rgb(color_buffer_sampler_(uv - vector2(0, tex_offset.y * i))) * weight[i];
            }
        }
        return color_rgba(result, 1);
    }
private:
    const model* mesh_;
    texture color_buffer_;
    sampler2 color_buffer_sampler_;
    vector2 v_uv_[3];
    bool horizontal_;
};

class bloom_shader : public basic_shader {
public:
    bloom_shader(const model& mesh, texture scene_tex, texture blur_tex) 
        : mesh_(&mesh)
    {
        scene_tex_ = std::move(scene_tex);
        blur_tex_ = std::move(blur_tex);
        scene_sampler_.bind_texture(scene_tex_);
        blur_sampler_.bind_texture(blur_tex_);
    }

    virtual vector4 vert(int n) override {
        auto pos = mesh_->get_vertex(n);
        v_uv_[n % 3] = mesh_->get_uv(n);
        return vector4(pos, 1);
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto uv = frag_lerp(v_uv_, bar);

        auto scene_color = scene_sampler_(uv);
        auto blur_color = blur_sampler_(uv);

        return color_rgba(scene_color + blur_color, 1);
    }
private:
    const model* mesh_;
    texture scene_tex_;
    texture blur_tex_;
    sampler2 scene_sampler_;
    sampler2 blur_sampler_;
    vector2 v_uv_[3];
};

int main() {
    try {
        camera cam;
        cam.pos.x = 0;
        cam.pos.y = 0.65;
        cam.pos.z = 2;
        cam.yaw = -90;
        cam.pitch = -15;

        model diablo;
        model quad;
        diablo.load("assets/models/diablo3_pose.obj");
        quad.load("assets/models/quad.obj");

        directional_light light;
        light.dir = vector3(0, 0.65, 2);
        light.ambient = color_rgb(0.1);
        light.diffuse = color_rgb(1.0);
        light.specular = color_rgb(0.5);

        framebuffer fb(1024, 1024);
        renderer r(fb);

        auto mvp = cam.proj(fb.aspect()) * cam.view();

        fb.clear({0, 0, 0, 1});
        position_shader ps(mvp, diablo);
        r.render(diablo.num_vertices(), ps);

        fb.clear({0, 0, 0, 1});
        normal_shader ns(mvp, diablo);
        r.render(diablo.num_vertices(), ns);

        fb.clear({0, 0, 0, 1});
        diffuse_shader ds(mvp, diablo);
        r.render(diablo.num_vertices(), ds);

        fb.clear({0, 0, 0, 1});
        specular_shader ss(mvp, diablo);
        r.render(diablo.num_vertices(), ss);

        fb.clear({0, 0, 0, 1});
        emission_shader es(mvp, diablo);
        r.render(diablo.num_vertices(), es);

        fb.write("image.pam");
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}