#ifndef BOX_POSITION_SHADER_HPP
#define BOX_POSITION_SHADER_HPP

#include "shader.hpp"

namespace box {
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
}

#endif