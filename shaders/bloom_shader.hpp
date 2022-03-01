#ifndef BOX_BLOOM_SHADER_HPP
#define BOX_BLOOM_SHADER_HPP

#include "shader.hpp"

namespace box {
    class bloom_shader : public basic_shader {
public:
    bloom_shader(const model& mesh, const texture& scene, const texture& blur) 
            : mesh_(&mesh)
        {
            scene_sampler_.bind_texture(scene);
            blur_sampler_.bind_texture(blur);
        }

        virtual vector4 vert(int n) override {
            auto pos = mesh_->get_vertex(n);
            v_uv_[n % 3] = mesh_->get_uv(n);
            return vector4(pos, 1);
        }

        virtual std::optional<color_rgba> frag(vector3 bar) override {
            auto uv = frag_lerp(v_uv_, bar);

            auto scene_color = scene_sampler_(uv);
            auto blur_color = blur_sampler_(uv);

            return color_rgba(scene_color + blur_color, 1);
        }
    private:
        const model* mesh_;
        sampler2 scene_sampler_;
        sampler2 blur_sampler_;
        vector2 v_uv_[3];
    };
}

#endif