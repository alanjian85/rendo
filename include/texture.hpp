#ifndef RAYSTER_TEXTURE_HPP
#define RAYSTER_TEXTURE_HPP

#include <iostream>
#include <string>
#include <vector>

#include "color.hpp"

namespace rayster {
    class texture {
    public:
        using size_type = std::vector<color_rgb>::size_type;

        void resize(size_type width, size_type height) {
            width_ = width;
            pixels_.resize(width * height);
        }

        size_type width() const noexcept {
            return width_;
        }

        size_type height() const noexcept {
            return pixels_.size() / width_;
        }

        color_rgb& operator()(size_type x, size_type y) noexcept {
            auto index = y * width_ + x;
            return pixels_[index];
        }

        const color_rgb& operator()(size_type x, size_type y) const noexcept {
            auto index = y * width_ + x;
            return pixels_[index];
        }
    private:
        size_type width_;
        std::vector<color_rgb> pixels_;
    };

    std::istream& operator>>(std::istream& lhs, texture& rhs);
}

#endif