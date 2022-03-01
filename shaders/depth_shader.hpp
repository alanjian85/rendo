#ifndef BOX_DEPTH_SHADER_HPP
#define BOX_DEPTH_SHADER_HPP

#include "shader.hpp"

namespace box {
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
}

#endif