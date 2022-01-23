#ifndef RAYSTER_TEXTURE_HPP
#define RAYSTER_TEXTURE_HPP

#include <filesystem>
#include <string>
#include <vector>

#include "color.hpp"
#include "vector.hpp"

namespace rayster {
    class texture {
    public:
        using size_type = std::vector<color_rgba>::size_type;

        texture() : width_(0), height_(0) {}

        void load(const std::filesystem::path& path);

        size_type width() const {
            return width_;
        }

        size_type height() const {
            return pixels_.size() / height_;
        }

        color_rgba& operator()(size_type x, size_type y) {
            auto index = y * width_ + x;
            return pixels_[index];
        }

        const color_rgba& operator()(size_type x, size_type y) const {
            auto index = y * width_ + x;
            return pixels_[index];
        }
    private:
        void load_ppm(const std::string& path);
        void load_pam(const std::string& path);

        size_type width_, height_;
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
        sampler2()
            : wrap_(wrapping::repeat),
              border_{0, 0, 0, 0},
              tex_(nullptr)
        {

        }

        void bind_texture(const texture& tex) {
            tex_ = &tex;
        }

        wrapping wrap() const {
            return wrap_;
        }

        void set_wrap(wrapping wrap) {
            wrap_ = wrap;
        }

        void set_border(color_rgba border) {
            border_ = border;
        }

        color_rgba border() const {
            return border_;
        }

        color_rgba operator()(vector3 tex_coord) const;
    private:
        wrapping wrap_;
        color_rgba border_;
        const texture* tex_;
    };

    class sampler_cube {
    public:
        sampler_cube() noexcept
            : wrap_s_(wrapping::repeat),
              wrap_t_(wrapping::repeat),
              wrap_r_(wrapping::repeat),
              right_(nullptr),
              left_(nullptr),
              top_(nullptr),
              bottom_(nullptr),
              back_(nullptr),
              front_(nullptr)
        {

        }

        void bind_right(const texture& right) {
            right_ = &right;
        }

        void bind_left(const texture& left) {
            left_ = &left;
        }

        void bind_top(const texture& top) {
            top_ = &top;
        }

        void bind_bottom(const texture& bottom) {
            bottom_ = &bottom;
        }

        void bind_back(const texture& back) {
            back_ = &back;
        }

        void bind_front(const texture& front) {
            front_ = &front;
        }

        wrapping wrap_s() const {
            return wrap_s_;
        }

        void set_wrap_s(wrapping wrap) {
            wrap_s_ = wrap;
        }

        wrapping wrap_t() const {
            return wrap_t_;
        }

        void set_wrap_t(wrapping wrap) {
            wrap_t_ = wrap;
        }

        wrapping wrap_r() const {
            return wrap_r_;
        }

        void set_wrap_r(wrapping wrap) {
            wrap_r_ = wrap;
        }

        void set_border(color_rgba border) {
            border_ = border;
        }

        color_rgba border() const {
            return border_;
        }

        color_rgba operator()(vector3 tex_coord) const;
    private:
        wrapping wrap_s_;
        wrapping wrap_t_;
        wrapping wrap_r_;
        color_rgba border_;

        const texture* right_;
        const texture* left_;
        const texture* top_;
        const texture* bottom_;
        const texture* back_;
        const texture* front_;
    };
}

#endif