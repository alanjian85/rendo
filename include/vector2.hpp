#ifndef RAYSTER_VECTOR2_HPP
#define RAYSTER_VECTOR2_HPP

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
}

#endif