#ifndef SENTINEL_DETAIL_VECTOR3_HPP
#define SENTINEL_DETAIL_VECTOR3_HPP

#include <cmath>

#include "vector.hpp"

namespace sentinel {
    template <typename T>
    struct vector<T, 3> {
        friend vector operator+(vector lhs, vector rhs) noexcept {
            return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z}; 
        }

        friend vector operator-(vector lhs, vector rhs) noexcept {
            return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
        }

        friend vector operator+(vector lhs, T rhs) noexcept {
            return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs};
        }

        friend vector operator-(vector lhs, T rhs) noexcept {
            return {lhs.x - rhs, lhs.y - rhs, lhs.z - rhs};
        }

        friend vector operator*(vector lhs, T rhs) noexcept {
            return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs}; 
        } 

        friend vector operator/(vector lhs, T rhs) noexcept {
            return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
        }

        constexpr vector() = default;
        constexpr vector(T x_, T y_, T z_) 
            : x(x_),
              y(y_),
              z(z_)
        {
            
        }

        constexpr vector operator-() const noexcept {
            return {-x, -y, -z};
        }

        constexpr T length_squared() const noexcept {
            return x * x + y * y + z * z;
        }

        constexpr T length() const noexcept {
            return std::sqrt(length_squared());
        }

        constexpr vector normalize() const noexcept {
            auto len = length();
            if (len == 0)
                return {0, 0, 0};
            else
                return {x / len, y / len, z / len};
        }

        T x;
        T y;
        T z;
    };
}

#endif
