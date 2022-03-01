#ifndef BOX_BRIGHT_SHADER_HPP
#define BOX_BRIGHT_SHADER_HPP

#include "shader.hpp"

namespace box {
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
}

#endif