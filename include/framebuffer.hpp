#ifndef RAYSTER_FRAMEBUFFER_HPP
#define RAYSTER_FRAMEBUFFER_HPP

#include <iostream>
#include <vector>

#include "color.hpp"
#include "vec.hpp"

namespace rayster {
    struct pixel {
        color_rgb color;
    };

    class framebuffer {
    public:
        using size_type = ivec2;
        using iterator = std::vector<pixel>::iterator;
        using const_iterator = std::vector<pixel>::const_iterator;

        framebuffer() noexcept = default;
        framebuffer(size_type size)
            : size_(size),
              pixels_(size.x * size.y)
        {

        }

        size_type size() const noexcept {
            return size_;
        }

        auto width() const noexcept {
            return size_.x;
        }
        
        auto height() const noexcept {
            return size_.y;
        }

        void clear(color_rgb color) noexcept {
            for (auto& p : *this) {
                p.color = color;
            }
        }

        pixel& operator[](size_type index) noexcept {
            auto pos = index.y * size_.x + index.x;
            return {pixels_[pos]};
        }

        const pixel& operator[](size_type index) const noexcept {
            auto pos = index.y * size_.x + index.x;
            return {pixels_[pos]};
        }

        const_iterator begin() const noexcept {
            return pixels_.begin();
        }

        iterator begin() noexcept {
            return pixels_.begin();
        }

        const_iterator end() const noexcept {
            return pixels_.end();
        }

        iterator end() noexcept {
            return pixels_.end();
        }

        const_iterator cbegin() const noexcept {
            return pixels_.cbegin();
        }

        const_iterator cend() const noexcept {
            return pixels_.cend();
        }
    private:
        ivec2 size_;
        std::vector<pixel> pixels_;
    };

    std::ostream& operator<<(std::ostream& lhs, const framebuffer& rhs) noexcept;
}

#endif
