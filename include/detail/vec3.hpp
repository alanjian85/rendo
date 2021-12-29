#ifndef RAYSTER_VEC3_HPP
#define RAYSTER_VEC3_HPP

namespace rayster {
    template <typename T>
    struct vec<T, 3> {
        using value_type = T;
        using size_type = std::size_t;

        vec() : x(), y() {}
        vec(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

        T& operator[](size_type index) noexcept {
            return index == 0 ? x : y;
        }

        T operator[](size_type index) const noexcept {
            return index == 0 ? x : y;
        }

        T x;
        T y;
        T z;
    };

    template <typename T>
    inline vec<T, 3> cross(vec<T, 3> lhs, vec<T, 3> rhs) noexcept {
        return {
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x
        };
    }

    using vec3 = vec<double, 3>;
    using ivec3 = vec<int, 3>;
}

#endif