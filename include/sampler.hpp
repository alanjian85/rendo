#ifndef RAYSTER_SAMPLER_HPP
#define RAYSTER_SAMPLER_HPP

#include "texture.hpp"
#include "vector2.hpp"

namespace rayster {
    enum class wrapping {
        repeat,
        repeat_mirrored,
        clamp_to_edge,
        clamp_to_border
    };

    class sampler {
    public:
        sampler() noexcept 
            : wrap_(wrapping::repeat) 
        {

        }

        wrapping wrap() const noexcept {
            return wrap_;
        }

        void wrap(wrapping wrap) noexcept {
            wrap_ = wrap;
        }

        void set_border(color_rgb border) noexcept {
            border_ = border;
        }

        color_rgb border() const noexcept {
            return border_;
        }

        color_rgb operator()(const texture& tex, vector2 v) const noexcept;
    private:
        wrapping wrap_;
        color_rgb border_;
    };
}

#endif