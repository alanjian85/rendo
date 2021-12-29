#ifndef RAYSTER_DETAIL_VEC2_HPP
#define RAYSTER_DETAIL_VEC2_HPP

#include <iostream>
#include <limits>

namespace rayster {
    template <typename T>
    struct vec<T, 2> {
        using value_type = T;
        using size_type = std::size_t;

        static inline vec min() {
            return {
                std::numeric_limits<T>::min(),
                std::numeric_limits<T>::min()
            };
        }

        static inline vec max() noexcept {
            return {
                std::numeric_limits<T>::max(),
                std::numeric_limits<T>::max()
            };
        }

        vec() : x(), y() {}
        vec(T x_, T y_) : x(x_), y(y_) {}

        T& operator[](size_type index) noexcept {
            return index == 0 ? x : y;
        }

        T operator[](size_type index) const noexcept {
            return index == 0 ? x : y;
        }

        T x;
        T y;
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& lhs, vec<T, 2> rhs) noexcept {
        lhs << '(' << rhs.x << ' ' << rhs.y << ')';
        return lhs;
    }

    using vec2 = vec<double, 2>;
    using ivec2 = vec<int, 2>;
}

#endif