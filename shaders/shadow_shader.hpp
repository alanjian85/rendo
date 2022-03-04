#ifndef BOX_SHADOW_SHADER_HPP
#define BOX_SHADOW_SHADER_HPP

#include "shader.hpp"

namespace box {
    class shadow_shader : public basic_shader {
    public:
        shadow_shader(matrix4 light_proj, matrix4 light_view, const model& mesh) {
            light_proj_ = light_proj;
            light_view_ = light_view;
            mesh_ = &mesh;
        }
    
        virtual vector4 vert(int n) override {
            auto pos = mesh_->get_vertex(n);
            return light_proj_ * light_view_ * vector4(pos, 1);
        }
    
        virtual std::optional<color_rgba> frag(vector3 bar) override {
            return color_rgba(0, 0, 0, 1);
        }
    private:
        matrix4 light_proj_;
        matrix4 light_view_;
        const model* mesh_;
    };
}

#endif