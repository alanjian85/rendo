#ifndef RAYSTER_DETAIL_VEC2_HPP
#define RAYSTER_DETAIL_VEC2_HPP

namespace rayster {
    template <typename T>
    struct vec<T, 2> {
        using value_type = T;
        using size_type = std::size_t;

        vec() : x(), y() {}
        vec(T x_, T y_) : x(x_), y(y_) {}

        T& operator[](size_type index) const noexcept {
            return index == 0 ? x : y;
        }

        T operator[](size_type index) const noexcept {
            return index == 0 ? x : y;
        }

        T x;
        T y;
    };

    using vec2 = vec<double, 2>;
    using ivec2 = vec<int, 2>;
}

#endif