#ifndef RAYSTER_TEXTURE_HPP
#define RAYSTER_TEXTURE_HPP

#include <string>
#include <vector>

#include "color.hpp"
#include "vector.hpp"

namespace rayster {
    class texture {
    public:
        using size_type = std::vector<color_rgba>::size_type;

        void load(const std::string& path);

        void resize(size_type width, size_type height) {
            width_ = width;
            pixels_.resize(width * height);
        }

        size_type width() const noexcept {
            return width_;
        }

        size_type height() const noexcept {
            if (width_ == 0)
                return 0;
            return pixels_.size() / width_;
        }

        color_rgba& operator()(size_type x, size_type y) noexcept {
            auto index = y * width_ + x;
            return pixels_[index];
        }

        const color_rgba& operator()(size_type x, size_type y) const noexcept {
            auto index = y * width_ + x;
            return pixels_[index];
        }
    private:
        size_type width_;
        std::vector<color_rgba> pixels_;
    };

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