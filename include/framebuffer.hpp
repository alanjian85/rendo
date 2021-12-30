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
        using size_type = std::size_t;

        framebuffer() noexcept = default;
        framebuffer(size_type width, size_type height)
            : height_(height),
              pixels_(width * height)
        {

        }

        size_type width() const noexcept {
            return static_cast<size_type>(pixels_.size() / height_);
        }
        
        size_type height() const noexcept {
            return height_;
        }

        void clear(color_rgb color) noexcept {
            for (auto& p : pixels_) {
                p.color = color;
            }
        }

        pixel& operator()(size_type x, size_type y) noexcept {
            auto index = y * height_ + x;
            return {pixels_[index]};
        }

        const pixel& operator()(size_type x, size_type y) const noexcept {
            auto index = y * height_ + x;
            return {pixels_[index]};
        }
    private:
        size_type height_;
        std::vector<pixel> pixels_;
    };

    std::ostream& operator<<(std::ostream& lhs, const framebuffer& rhs) noexcept;
}

#endif
