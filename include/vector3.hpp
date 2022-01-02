#ifndef RAYSTER_VECTOR3_HPP
#define RAYSTER_VECTOR3_HPP

#include <cmath>

namespace rayster {
    struct vector3 {
        double x;
        double y;
        double z;

        auto length_squared() const noexcept {
            return x * x + y * y + z * z;
        }

        auto length() const noexcept {
            return std::sqrt(length_squared());
        }

        vector3 normalize() const noexcept {
            auto len = length();
            if (len == 0)
                return {0, 0, 0};
            return {x / len, y / len, z / len};
        }
    };

    inline vector3 operator-(vector3 lhs, vector3 rhs) noexcept {
        return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
    }

    inline double dot(vector3 lhs, vector3 rhs) noexcept {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    inline vector3 cross(vector3 lhs, vector3 rhs) noexcept {
        return {
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x
        };
    }
}

#endif