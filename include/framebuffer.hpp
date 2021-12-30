#ifndef RAYSTER_FRAMEBUFFER_HPP
#define RAYSTER_FRAMEBUFFER_HPP

#include <cstdlib>
#include <iostream>
#include <vector>

#include "color.hpp"

namespace rayster {
    struct pixel {
        color_rgb color;
    };

    class framebuffer {
    public:
        using size_type = std::vector<pixel>::size_type;

        framebuffer() noexcept : width_() {}
        framebuffer(size_type width, size_type height)
            : width_(width),
              pixels_(width * height)
        {

        }

        size_type width() const noexcept {
            return width_;
        }
        
        size_type height() const noexcept {
            return pixels_.size() / width_;
        }

        void clear(color_rgb color) noexcept {
            for (auto& p : pixels_) {
                p.color = color;
            }
        }

        pixel& operator()(size_type x, size_type y) noexcept {
            auto index = y * width_ + x;
            return {pixels_[index]};
        }

        const pixel& operator()(size_type x, size_type y) const noexcept {
            auto index = y * width_ + x;
            return {pixels_[index]};
        }
    private:
        size_type width_;
        std::vector<pixel> pixels_;
    };

    std::ostream& operator<<(std::ostream& lhs, const framebuffer& rhs) noexcept;
}

#endif
