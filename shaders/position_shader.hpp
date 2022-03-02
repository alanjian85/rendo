#ifndef BOX_POSITION_SHADER_HPP
#define BOX_POSITION_SHADER_HPP

#include "shader.hpp"

namespace box {
    class position_shader : public basic_shader {
    public:
        position_shader(matrix4 proj, matrix4 view, const model& mesh) {
            proj_ = proj;
            view_ = view;
            mesh_ = &mesh;
        }
    
        virtual vector4 vert(int n) override {
            auto pos = mesh_->get_vertex(n);
            v_pos_[n % 3] = vector3(view_ * vector4(pos, 1));
            return proj_ * view_ * vector4(pos, 1);
        }
    
        virtual std::optional<color_rgba> frag(vector3 bar) override {
            auto pos = frag_lerp(v_pos_, bar);
            return color_rgba(pos.x, pos.y, pos.z, 1);
        }
    private:
        matrix4 proj_;
        matrix4 view_;
        const model* mesh_;
        vector3 v_pos_[3];
    };
}

#endif