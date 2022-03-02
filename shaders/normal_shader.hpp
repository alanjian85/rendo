#ifndef BOX_NORMAL_SHADER_HPP
#define BOX_NORMAL_SHADER_HPP

#include "shader.hpp"

namespace box {
    class normal_shader : public basic_shader {
    public:
        normal_shader(matrix4 proj, matrix4 view, const model& mesh) {
            proj_ = proj;
            view_ = view;
            mesh_ = &mesh;
        }

        virtual vector4 vert(int n) override {
            auto pos = mesh_->get_vertex(n);
            v_pos_[n % 3] = vector3(view_ * vector4(pos, 1));
            v_uv_[n % 3] = mesh_->get_uv(n);
            v_normal_[n % 3] = matrix3(view_.inverse().transpose()) * mesh_->get_normal(n);
            normal_sampler_.bind_texture(mesh_->get_mat(n)->normal_map);
            return proj_ * view_ * vector4(pos, 1);
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
        matrix4 proj_;
        matrix4 view_;
        const model* mesh_;
        vector3 v_pos_[3];
        vector2 v_uv_[3];
        vector3 v_normal_[3];
        matrix3 v_tbn_[3];
        sampler2 normal_sampler_;
    };
}

#endif