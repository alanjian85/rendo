#ifndef BOX_SPECULAR_SHADER_HPP
#define BOX_SPECULAR_SHADER_HPP

#include "shader.hpp"

namespace box {
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
}

#endif