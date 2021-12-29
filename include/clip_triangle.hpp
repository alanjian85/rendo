#ifndef RAYSTER_CLIP_TRIANGLE_HPP
#define RAYSTER_CLIP_TRIANGLE_HPP

#include <cstdlib>

#include "aabb.hpp"
#include "vec.hpp"

namespace rayster {
    struct clip_triangle {
        using size_type = std::size_t;

        ivec2 a;
        ivec2 b;
        ivec2 c;

        aabb bbox() const noexcept;
        vec3 barycentric(ivec2 v) const noexcept;

        ivec2& operator[](size_type index) noexcept {
            return index == 0 ? a : index == 1 ? b : c;
        }

        ivec2 operator[](size_type index) const noexcept {
            return index == 0 ? a : index == 1 ? b : c;
        }

        class iterator {
            friend bool operator!=(iterator lhs, iterator rhs) noexcept {
                return &lhs.tri_ != &rhs.tri_ || lhs.index_ != rhs.index_;
            }
        public:
            iterator(clip_triangle& tri, size_type index)
                : tri_(tri),
                  index_(index)
            {
                
            }

            ivec2& operator*() const noexcept {
                return tri_[index_];
            }

            iterator& operator++() noexcept {
                ++index_;
                return *this;
            }
        private:
            clip_triangle& tri_;
            size_type index_;  
        };

        class const_iterator {
            friend bool operator!=(const_iterator lhs, const_iterator rhs) noexcept {
                return &lhs.tri_ != &rhs.tri_ || lhs.index_ != rhs.index_;
            }
        public:
            const_iterator(const clip_triangle& tri, size_type index)
                : tri_(tri),
                  index_(index)
            {
                
            }

            ivec2 operator*() const noexcept {
                return tri_[index_];
            }

            const_iterator& operator++() noexcept {
                ++index_;
                return *this;
            }
        private:
            const clip_triangle& tri_;
            size_type index_;  
        };

        iterator begin() noexcept {
            return {*this, 0};
        }

        const_iterator begin() const noexcept {
            return {*this, 0};
        }

        iterator end() noexcept {
            return {*this, 3};
        }

        const_iterator end() const noexcept {
            return {*this, 3};
        }

        const_iterator cbegin() const noexcept {
            return {*this, 0};
        }

        const_iterator cend() const noexcept {
            return {*this, 3};
        }
    };
}

#endif