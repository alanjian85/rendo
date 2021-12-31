#ifndef RAYSTER_SAMPLER_HPP
#define RAYSTER_SAMPLER_HPP

#include "texture.hpp"
#include "vector2.hpp"

namespace rayster {
    enum class wrapping {
        repeat
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

        void set_wrap(wrapping wrap) noexcept {
            wrap_ = wrap;
        }

        color_rgb operator()(const texture& tex, vector2 v) const noexcept;
    private:
        wrapping wrap_;
    };
}

#endif