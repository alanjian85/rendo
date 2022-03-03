#ifndef BOX_SSAO_BLUR_SHADER
#define BOX_SSAO_BLUR_SHADER

#include "shader.hpp"
#include "texture.hpp"

namespace box {
    class ssao_blur_shader : public basic_shader {
    public:
        ssao_blur_shader(const model& mesh, const texture& ssao) {
            mesh_ = &mesh;
            ssao_sampler_.bind_texture(ssao);
        }

        virtual vector4 vert(int n) override {
            auto pos = mesh_->get_vertex(n);
            v_uv_[n % 3] = mesh_->get_uv(n);
            return vector4(pos, 1);
        }

        virtual std::optional<color_rgba> frag(vector3 bar) override {
            auto uv = frag_lerp(v_uv_, bar);

            auto& ssao = ssao_sampler_.get_texture();
            auto texel_size = vector2(1.0 / ssao.width(), 1.0 / ssao.height());

            auto result = 0.0;
            for (int x = -2; x < 2; ++x) {
                for (int y = -2; y < 2; ++y) {
                    auto offset = vector2(x, y) * texel_size;
                    result += ssao_sampler_(uv + offset).r;
                }
            }

            return color_rgba(color_rgb(result / (4.0 * 4.0)), 1.0);
        }
    private:
        const model* mesh_;
        vector2 v_uv_[3];
        sampler2 ssao_sampler_;
    };
}

#endif