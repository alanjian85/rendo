#ifndef RAYSTER_FRAMEBUFFER_HPP
#define RAYSTER_FRAMEBUFFER_HPP

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

        class iterator {
            friend bool operator!=(iterator lhs, iterator rhs) noexcept {
                return &lhs.fb_ != &rhs.fb_ || lhs.index_ != rhs.index_;
            }
        public:
            iterator(framebuffer& fb, size_type index) noexcept
                : fb_(fb),
                  index_(index)
            {
            
            }

            pixel& operator*() const noexcept {
                return {fb_.pixels_[index_]};
            }

            void operator++() noexcept {
                ++index_;
            }
        private:
            framebuffer& fb_;
            size_type index_;
        };

        class const_iterator {
            friend bool operator!=(const_iterator lhs, const_iterator rhs) noexcept {
                return &lhs.fb_ != &rhs.fb_ || lhs.index_ != rhs.index_;
            }
        public:
            const_iterator(const framebuffer& fb, size_type index) noexcept
                : fb_(fb),
                  index_(index)
            {
            
            }

            const pixel& operator*() const noexcept {
                return {fb_.pixels_[index_]};
            }

            void operator++() noexcept {
                ++index_;
            }
        private:
            const framebuffer& fb_;
            size_type index_;
        };

        framebuffer() noexcept 
            : width_(),
              height_()
        {
        
        }
       
        framebuffer(size_type width, size_type height)
            : width_(width),
              height_(height),
              pixels_(width * height)
        {

        }

        void resize(size_type width, size_type height) {
            width_ = width;
            height_ = height;
            pixels_.resize(width * height);
        }

        size_type width() const noexcept {
            return width_;
        }
        
        size_type height() const noexcept {
            return height_;
        }

        pixel& operator()(int x, int y) noexcept {
            auto index = y * width_ + x;
            return {pixels_[index]};
        }

        const pixel& operator()(int x, int y) const noexcept {
            auto index = y * width_ + x;
            return {pixels_[index]};
        }

        const_iterator begin() const noexcept {
            return {*this, 0};
        }

        iterator begin() noexcept {
            return {*this, 0};
        }

        const_iterator end() const noexcept {
            return {*this, width_ * height_};
        }

        iterator end() noexcept {
            return {*this, width_ * height_};
        }

        void clear(color_rgb color) noexcept {
            for (auto& p : *this) {
                p.color = color;
            }
        }
    private:
        size_type width_;
        size_type height_;
        
        std::vector<pixel> pixels_;
    };

    std::ostream& operator<<(std::ostream& lhs, const framebuffer& rhs) noexcept;
}

#endif
