#ifndef RAYSTER_FRAMEBUFFER_HPP
#define RAYSTER_FRAMEBUFFER_HPP

#include <cstdlib>
#include <iostream>
#include <vector>

#include "color.hpp"

namespace rayster {
    struct pixel {
        color_rgba color;
        double depth;
    };

    class framebuffer {
    public:
        using size_type = std::vector<pixel>::size_type;

        virtual ~framebuffer() = default;

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
            if (width_ == 0)
                return 0;
            return pixels_.size() / width_;
        }

        void clear(color_rgba color) noexcept {
            for (auto& p : pixels_) {
                p.color = color;
                p.depth = 1;
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

        bool depth_test(size_type x, size_type y, double z) const noexcept {
            return z < (*this)(x, y).depth;
        }
    private:
        size_type width_;
        std::vector<pixel> pixels_;
    };
}

#endif
