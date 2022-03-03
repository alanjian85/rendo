#ifndef BOX_SSAO_SHADER_HPP
#define BOX_SSAO_SHADER_HPP

#include <random>
#include <vector>

#include "shader.hpp"
#include "texture.hpp"

namespace box {
    class ssao_shader : public basic_shader {
    public:
        ssao_shader(matrix4 proj, const model& mesh, const texture& position, const texture& normal, int width, int height) {
            proj_ = proj;
            mesh_ = &mesh;
            position_sampler_.bind_texture(position);
            normal_sampler_.bind_texture(normal);

            std::uniform_real_distribution<double> dist(0.0, 1.0);
            std::default_random_engine engine(std::time(nullptr));
            for (int i = 0; i < 64; ++i) {
                vector3 sample;
                sample.x = dist(engine) * 2 - 1;
                sample.y = dist(engine) * 2 - 1;
                sample.z = dist(engine);

                sample = sample.normalize();
                sample *= dist(engine);

                auto scale = i / 64.0;
                scale = lerp(0.1, 1.0, scale * scale);
                sample *= scale;

                samples_.push_back(sample);
            }

            noise_ = texture(4, 4);
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    vector3 noise;
                    noise.x = dist(engine) * 2 - 1;
                    noise.y = dist(engine) * 2 - 1;
                    noise.z = 0;
                    noise_(i, j) = color_rgba(noise.x, noise.y, noise.z, 1);
                }
            }
            noise_sampler_.bind_texture(noise_);

            noise_scale_.x = width / 4.0;
            noise_scale_.y = height / 4.0;
        }

        virtual vector4 vert(int n) override {
            auto pos = mesh_->get_vertex(n);
            v_uv_[n % 3] = mesh_->get_uv(n);
            return vector4(pos, 1);
        }

        virtual std::optional<color_rgba> frag(vector3 bar) override {
            auto uv = frag_lerp(v_uv_, bar);

            auto position = vector3(position_sampler_(uv));
            auto normal = vector3(normal_sampler_(uv));
            auto randvec = vector3(noise_sampler_(uv * noise_scale_));

            auto tangent = (randvec - normal * dot(randvec, normal)).normalize();
            auto bitangent = cross(normal, tangent);
            matrix3 tbn(
                tangent.x, bitangent.x, normal.x,
                tangent.y, bitangent.y, normal.y,
                tangent.z, bitangent.z, normal.z
            );

            auto occulusion = 0.0;
            auto radius = 0.5;
            auto bias = 0.025;
            for (auto sample : samples_) {
                auto sample_pos = tbn * sample;
                sample_pos = position + sample_pos * radius;

                auto offset = vector4(sample_pos, 1.0);
                offset = proj_ * offset;
                auto clip_offset = vector3(offset) / offset.w;
                clip_offset = clip_offset * 0.5 + 0.5;

                auto depth = position_sampler_(vector2(clip_offset)).b;
                auto range_check = smoothstep(0.0, 1.0, radius / std::abs(position.z - depth));
                occulusion += (depth >= sample_pos.z + bias ? 1.0 : 0.0) * range_check;
            }

            occulusion = 1.0 - (occulusion / samples_.size());
            return color_rgba(occulusion, occulusion, occulusion, 1.0);
        }
    private:
        matrix4 proj_;
        const model* mesh_;
        vector2 v_uv_[3];
        sampler2 position_sampler_;
        sampler2 normal_sampler_;

        std::vector<vector3> samples_;
        texture noise_;
        sampler2 noise_sampler_;
        vector2 noise_scale_;
    };
}

#endif