#ifndef BOX_EMISSION_SHADER_HPP
#define BOX_EMISSION_SHADER_HPP

#include "shader.hpp"

namespace box {
    class emission_shader : public basic_shader {
    public:
        emission_shader(matrix4 proj, matrix4 view, const model& mesh) {
            proj_ = proj;
            view_ = view;
            mesh_ = &mesh;
        }
    
        virtual vector4 vert(int n) override {
            auto pos = mesh_->get_vertex(n);
            v_uv_[n % 3] = mesh_->get_uv(n);
            emission_sampler_.bind_texture(mesh_->get_mat(n)->emission_map);
            return proj_ * view_ * vector4(pos, 1);
        }
    
        virtual std::optional<color_rgba> frag(vector3 bar) override {
            //auto uv = frag_lerp(v_uv_, bar);
            return color_rgba(0, 0, 0, 1); //emission_sampler_(uv);
        }
    private:
        matrix4 proj_;
        matrix4 view_;
        const model* mesh_;
        vector2 v_uv_[3];
        sampler2 emission_sampler_;
    };
}

#endif
