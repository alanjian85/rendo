#ifndef SENTINEL_FRAMEBUFFER_HPP
#define SENTINEL_FRAMEBUFFER_HPP

#include <iostream>
#include <vector>

#include "color.hpp"

namespace sentinel {
    struct pixel {
        color_rgb& color;
    };

    struct const_pixel {
        const color_rgb& color;
    };

    class framebuffer {
    public:
        class iterator {
            friend bool operator!=(iterator lhs, iterator rhs) noexcept;
        public:
            iterator(framebuffer& fb, int index) noexcept
                : fb_(fb),
                  index_(index)
            {
            
            }

            pixel operator*() const noexcept {
                return {fb_.color_[index_]};
            }

            void operator++() noexcept {
                ++index_;
            }
        private:
            framebuffer& fb_;
            int index_;
        };

        class const_iterator {
            friend bool operator!=(const_iterator lhs, const_iterator rhs) noexcept;
        public:
            const_iterator(const framebuffer& fb, int index) noexcept
                : fb_(fb),
                  index_(index)
            {
            
            }

            const_pixel operator*() const noexcept {
                return {fb_.color_[index_]};
            }

            void operator++() noexcept {
                ++index_;
            }
        private:
            const framebuffer& fb_;
            int index_;
        };

        framebuffer() noexcept = default;
        framebuffer(int width, int height) {
            resize(width, height);
        }

        void resize(int width, int height) {
            width_ = width;
            height_ = height;
            color_.resize(width * height);
        }

        int width() const noexcept {
            return width_;
        }
        
        int height() const noexcept {
            return height_;
        }

        pixel operator()(int x, int y) noexcept {
            auto index = y * width_ + x;
            return {color_[index]};
        }

        const_pixel operator()(int x, int y) const noexcept {
            auto index = y * width_ + x;
            return {color_[index]};
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
            for (auto p : *this) {
                p.color = color;
            }
        }
    private:
        int width_ = 0;
        int height_ = 0;
        
        std::vector<color_rgb> color_;
    };

    inline bool operator!=(framebuffer::iterator lhs, framebuffer::iterator rhs) noexcept {
        return &lhs.fb_ != &rhs.fb_ || lhs.index_ != rhs.index_;
    }

    inline bool operator!=(framebuffer::const_iterator lhs, framebuffer::const_iterator rhs) noexcept {
        return &lhs.fb_ != &rhs.fb_ || lhs.index_ != rhs.index_;
    }

    std::ostream& operator<<(std::ostream& lhs, const framebuffer& rhs) noexcept;
}

#endif
