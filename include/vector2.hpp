#ifndef RAYSTER_vector2_HPP
#define RAYSTER_vector2_HPP

#include <cstdlib>
#include <cmath>

namespace rayster {
    struct vector2 { 
        constexpr vector2() 
            : x(), y() 
        {
        
        }
        constexpr vector2(double x_, double y_) 
            : x(x_), y(y_)
        {
            
        }

        constexpr double& operator[](std::size_t index) noexcept {
            return index == 0 ? x : y;
        }

        constexpr const double& operator[](std::size_t index) const noexcept {
            return index == 0 ? x : y; 
        }

        constexpr vector2 operator-() const noexcept {
            return {-x, -y};
        }

        constexpr vector2& operator+=(vector2 rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        constexpr vector2& operator-=(vector2 rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        constexpr vector2& operator+=(double rhs) noexcept {
            x += rhs;
            y += rhs;
            return *this;
        }

        constexpr vector2& operator-=(double rhs) noexcept {
            x -= rhs;
            y -= rhs;
            return *this;
        }

        constexpr vector2& operator*=(double rhs) noexcept {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        constexpr vector2& operator/=(double rhs) noexcept {
            x /= rhs;
            y /= rhs;
            return *this;
        }

        constexpr double length_squared() const noexcept {
            return x * x + y * y;
        }

        constexpr double length() const noexcept {
            return std::sqrt(length_squared());
        }

        constexpr vector2 normalize() const noexcept {
            auto len = length();
            if (len == 0)
                return {0, 0};
            else
                return {x / len, y / len};
        }

        double x;
        double y;
    };

    constexpr inline vector2 operator+(vector2 lhs, vector2 rhs) noexcept {
        return {lhs.x + rhs.x, lhs.y + rhs.y};
    }

    constexpr inline vector2 operator-(vector2 lhs, vector2 rhs) noexcept {
        return {lhs.x - rhs.x, lhs.y - rhs.y};
    }

    constexpr inline vector2 operator+(vector2 lhs, double rhs) noexcept {
        return {lhs.x + rhs, lhs.y + rhs};
    }

    constexpr inline vector2 operator-(vector2 lhs, double rhs) noexcept {
        return {lhs.x - rhs, lhs.y - rhs};
    }

    constexpr inline vector2 operator*(vector2 lhs, double rhs) noexcept {
        return {lhs.x * rhs, lhs.y * rhs};
    }

    constexpr inline vector2 operator/(vector2 lhs, double rhs) noexcept {
        return {lhs.x / rhs, lhs.y / rhs};
    }
}

#endif
