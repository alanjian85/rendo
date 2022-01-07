#ifndef RAYSTER_SAMPLER2_HPP
#define RAYSTER_SAMPLER2_HPP

#include "texture.hpp"
#include "vector2.hpp"

namespace rayster {
    enum class wrapping {
        repeat,
        repeat_mirrored,
        clamp_to_edge,
        clamp_to_border
    };

    class sampler2 {
    public:
        sampler2() noexcept 
            : wrap_(wrapping::repeat) 
        {

        }

        wrapping wrap() const noexcept {
            return wrap_;
        }

        void wrap(wrapping wrap) noexcept {
            wrap_ = wrap;
        }

        void set_border(color_rgba border) noexcept {
            border_ = border;
        }

        color_rgba border() const noexcept {
            return border_;
        }

        void bind_texture(const texture& tex) noexcept {
            tex_ = &tex;
        }

        color_rgba operator()(vector2 uv) const noexcept;
    private:
        wrapping wrap_;
        color_rgba border_;
        const texture* tex_;
    };
}

#endif