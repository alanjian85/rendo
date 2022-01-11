#ifndef RAYSTER_VECTOR_HPP
#define RAYSTER_VECTOR_HPP

#include <cmath>
#include <limits>

namespace rayster {
    struct vector2 {
        double x;
        double y;

        vector2& operator*=(double rhs) noexcept {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        static vector2 min() noexcept {
            return {
                std::numeric_limits<double>::min(),
                std::numeric_limits<double>::min()
            };
        }

        static vector2 max() noexcept {
            return {
                std::numeric_limits<double>::max(),
                std::numeric_limits<double>::max()
            };
        }
    };

    inline vector2 operator+(vector2 lhs, vector2 rhs) noexcept {
        return {lhs.x + rhs.x, lhs.y + rhs.y};
    }

    inline vector2 operator*(vector2 lhs, double rhs) noexcept {
        return {lhs.x * rhs, lhs.y * rhs};
    }

    inline vector2 operator*(double lhs, vector2 rhs) noexcept {
        return rhs * lhs;
    }

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

    inline vector3 operator*(vector3 lhs, double rhs) noexcept {
        return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
    }

    inline vector3 operator*(double lhs, vector3 rhs) noexcept {
        return rhs * lhs;
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

    struct unit_vector3 {
        double x;
        double y;
        double z;

        unit_vector3(double x_, double y_, double z_) noexcept {
            auto len = std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
            if (len == 0) {
                x = 0;
                y = 0;
                z = 0;
                return;
            }

            x = x_ / len;
            y = y_ / len;
            z = z_ / len;
        }

        unit_vector3(vector3 rhs) noexcept
            : unit_vector3(rhs.x, rhs.y, rhs.z)
        {

        }
    };

    struct vector4 {
        double x;
        double y;
        double z;
        double w;
    
        vector4& operator*=(double rhs) noexcept {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            w *= rhs;
            return *this;
        }
    };
}

#endif