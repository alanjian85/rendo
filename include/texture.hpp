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

    class basic_sampler {
    public:
        basic_sampler() noexcept
            : wrap_(wrapping::repeat)
        {

        }

        virtual ~basic_sampler() noexcept = default;

        wrapping wrap() const noexcept {
            return wrap_;
        }

        void set_wrap(wrapping wrap) noexcept {
            wrap_ = wrap;
        }

        void set_border(color_rgba border) noexcept {
            border_ = border;
        }

        color_rgba border() const noexcept {
            return border_;
        }
    private:
        wrapping wrap_;
        color_rgba border_;
    };

    class sampler2 : public basic_sampler {
    public:
        using basic_sampler::basic_sampler;

        void bind_texture(const texture& tex) noexcept {
            tex_ = &tex;
        }

        color_rgba operator()(vector2 uv) const noexcept;
    private:
        const texture* tex_;
    };

    class sampler_cube : public basic_sampler {
    public:
        using basic_sampler::basic_sampler;

        void bind_right(const texture& right) noexcept {
            right_ = &right;
        }

        void bind_left(const texture& left) noexcept {
            left_ = &left;
        }

        void bind_top(const texture& top) noexcept {
            top_ = &top;
        }

        void bind_bottom(const texture& bottom) noexcept {
            bottom_ = &bottom;
        }

        void bind_back(const texture& back) noexcept {
            back_ = &back;
        }

        void bind_front(const texture& front) noexcept {
            front_ = &front;
        }

        color_rgba operator()(vector3 uvw) const noexcept;
    private:
        const texture* right_;
        const texture* left_;
        const texture* top_;
        const texture* bottom_;
        const texture* back_;
        const texture* front_;
    };
}

#endif