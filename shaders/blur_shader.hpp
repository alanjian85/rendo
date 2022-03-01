#ifndef BOX_BLUR_SHADER_HPP
#define BOX_BLUR_SHADER_HPP

#include "shader.hpp"

namespace box {
    class blur_shader : public basic_shader {
    public:
        blur_shader(const model& mesh, const texture& bright, bool horizontal) 
            : mesh_(&mesh)
        {
            bright_sampler_.bind_texture(bright);
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
            auto& bright = bright_sampler_.get_texture();
            auto tex_offset = vector2(1.0 / bright.width(), 1.0 / bright.height());
            auto result = color_rgb(bright_sampler_(uv)) * weight[0];
            if (horizontal_) {
                for (int i = 1; i < 5; ++i) {
                    result += color_rgb(bright_sampler_(uv + vector2(tex_offset.x * i, 0))) * weight[i];
                    result += color_rgb(bright_sampler_(uv - vector2(tex_offset.x * i, 0))) * weight[i];
                }
            } else {
                for (int i = 1; i < 5; ++i) {
                    result += color_rgb(bright_sampler_(uv + vector2(0, tex_offset.y * i))) * weight[i];
                    result += color_rgb(bright_sampler_(uv - vector2(0, tex_offset.y * i))) * weight[i];
                }
            }
            return color_rgba(result, 1);
        }
    private:
        const model* mesh_;
        sampler2 bright_sampler_;
        vector2 v_uv_[3];
        bool horizontal_;
    };
}

#endif