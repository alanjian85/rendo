#ifndef BOX_BRIGHT_SHADER_HPP
#define BOX_BRIGHT_SHADER_HPP

#include "shader.hpp"

namespace box {
    class bright_shader : public basic_shader {
    public:
        bright_shader(const model& mesh, const texture& scene) 
            : mesh_(&mesh)
        {
            scene_sampler_.bind_texture(scene);
        }

        virtual vector4 vert(int n) override {
            auto pos = mesh_->get_vertex(n);
            v_uv_[n % 3] = mesh_->get_uv(n);
            return vector4(pos, 1);
        }

        virtual std::optional<color_rgba> frag(vector3 bar) override {
            auto uv = frag_lerp(v_uv_, bar);

            auto color = scene_sampler_(uv);
            auto brightness = dot(vector3(color), vector3(0.2126, 0.7152, 0.0722));
            if (brightness > 1)
                return color_rgba(color, 1);
            else
                return color_rgba(0, 0, 0, 1);
        }
    private:
        const model* mesh_;
        sampler2 scene_sampler_;
        vector2 v_uv_[3];
    };
}

#endif