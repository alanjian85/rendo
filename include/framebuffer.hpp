#ifndef RAYSTER_FRAMEBUFFER_HPP
#define RAYSTER_FRAMEBUFFER_HPP

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

        framebuffer() : width_() {}
        framebuffer(size_type width, size_type height)
            : width_(width),
              pixels_(width * height)
        {

        }

        size_type width() const {
            return width_;
        }
        
        size_type height() const {
            if (width_ == 0)
                return 0;
            return pixels_.size() / width_;
        }

        double aspect() const {
            auto h = height();
            if (h == 0)
                return 0;
            return width_ / height();
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
            return z < (*this)(x, y).depth;
        }

        virtual void write(const std::string& path) const = 0;
    private:
        size_type width_;
        std::vector<pixel> pixels_;
    };

    class ppm_framebuffer : public framebuffer {
    public:
        using framebuffer::framebuffer;

        virtual void write(const std::string& path) const override;
    };

    class pam_framebuffer : public framebuffer {
    public:
        using framebuffer::framebuffer;
    
        virtual void write(const std::string& path) const override;
    };
}

#endif
