#ifndef RAYSTER_FRAMEBUFFER_HPP
#define RAYSTER_FRAMEBUFFER_HPP

#include <cassert>
#include <cstdlib>
#include <string>
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

        virtual ~framebuffer() noexcept = default;

        framebuffer() : width_(), height_() {}
        framebuffer(size_type width, size_type height)
            : width_(width), height_(height),
              pixels_(width * height)
        {

        }

        size_type width() const {
            return width_;
        }
        
        size_type height() const {
            return height_;
        }

        double aspect() const {
            assert(height_ != 0);
            return width_ / height_;
        }

        void clear(color_rgba color) {
            for (auto& p : pixels_) {
                p.color = color;
                p.depth = 1;
            }
        }

        pixel& operator()(size_type x, size_type y) {
            auto index = y * width_ + x;
            return {pixels_[index]};
        }

        const pixel& operator()(size_type x, size_type y) const {
            auto index = y * width_ + x;
            return {pixels_[index]};
        }

        bool depth_test(size_type x, size_type y, double z) const {
            return z > 0 && z < (*this)(x, y).depth;
        }

        void write(const std::string& path) const;
    private:
        size_type width_, height_;
        std::vector<pixel> pixels_;
    };
}

#endif
