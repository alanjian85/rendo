#ifndef RAYSTER_VECTOR2_HPP
#define RAYSTER_VECTOR2_HPP

#include <cstdlib>
#include <cmath>
#include <limits>

namespace rayster {
    struct vector2 { 
        inline static vector2 max() {
            return {
                std::numeric_limits<double>::max(),
                std::numeric_limits<double>::max()
            };
        }

        inline static vector2 min() {
            return {
                std::numeric_limits<double>::min(),
                std::numeric_limits<double>::min()
            };
        }
        
        vector2() 
            : x(), y() 
        {
        
        }
        
        vector2(double x_, double y_) 
            : x(x_), y(y_)
        {
            
        }

        double& operator[](std::size_t index) noexcept {
            return index == 0 ? x : y;
        }

        const double& operator[](std::size_t index) const noexcept {
            return index == 0 ? x : y; 
        }

        vector2 operator-() const noexcept {
            return {-x, -y};
        }

        vector2& operator+=(vector2 rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        vector2& operator-=(vector2 rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        vector2& operator+=(double rhs) noexcept {
            x += rhs;
            y += rhs;
            return *this;
        }

        vector2& operator-=(double rhs) noexcept {
            x -= rhs;
            y -= rhs;
            return *this;
        }

        vector2& operator*=(double rhs) noexcept {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        vector2& operator/=(double rhs) noexcept {
            x /= rhs;
            y /= rhs;
            return *this;
        }

        double length_squared() const noexcept {
            return x * x + y * y;
        }

        double length() const noexcept {
            return std::sqrt(length_squared());
        }

        vector2 normalize() const noexcept {
            auto len = length();
            if (len == 0)
                return {0, 0};
            else
                return {x / len, y / len};
        }

        double x;
        double y;
    };

    inline vector2 operator+(vector2 lhs, vector2 rhs) noexcept {
        return {lhs.x + rhs.x, lhs.y + rhs.y};
    }

    inline vector2 operator-(vector2 lhs, vector2 rhs) noexcept {
        return {lhs.x - rhs.x, lhs.y - rhs.y};
    }

    inline vector2 operator+(vector2 lhs, double rhs) noexcept {
        return {lhs.x + rhs, lhs.y + rhs};
    }

    inline vector2 operator-(vector2 lhs, double rhs) noexcept {
        return {lhs.x - rhs, lhs.y - rhs};
    }

    inline vector2 operator*(vector2 lhs, double rhs) noexcept {
        return {lhs.x * rhs, lhs.y * rhs};
    }

    inline vector2 operator/(vector2 lhs, double rhs) noexcept {
        return {lhs.x / rhs, lhs.y / rhs};
    }
}

#endif
