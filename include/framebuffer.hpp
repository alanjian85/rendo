#ifndef BOX_FRAMEBUFFER_HPP
#define BOX_FRAMEBUFFER_HPP

#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>

#include "color.hpp"

namespace box {
    struct pixel {
        color_rgba color;
        double depth;
    };

    class framebuffer {
    public:
        virtual ~framebuffer() noexcept = default;

        framebuffer() : width_(), height_() {}
        framebuffer(int width, int height)
            : width_(width), height_(height),
              pixels_(width * height)
        {

        }

        int width() const {
            return width_;
        }
        
        int height() const {
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

        pixel& operator()(int x, int y) {
            auto index = y * width_ + x;
            return {pixels_[index]};
        }

        const pixel& operator()(int x, int y) const {
            auto index = y * width_ + x;
            return {pixels_[index]};
        }

        bool depth_test(int x, int y, double z) const {
            return z >= -1 && z <= (*this)(x, y).depth;
        }

        void write(const std::string& path) const;
    private:
        int width_, height_;
        std::vector<pixel> pixels_;
    };
}

#endif
