#ifndef RAYSTER_VECTOR4_HPP
#define RAYSTER_VECTOR4_HPP

#include <cstdlib>
#include <cmath>

namespace rayster {
    struct vector4 { 
        constexpr vector4() 
            : x(), y(), z(), w()
        {
        
        }
        constexpr vector4(double x_, double y_, double z_, double w_) 
            : x(x_), y(y_), z(z_), w(w_)
        {
            
        }

        constexpr double& operator[](std::size_t index) noexcept {
            return index == 0 ? x : index == 1 ? y : z;
        }

        constexpr const double& operator[](std::size_t index) const noexcept {
            return index == 0 ? x : index == 1 ? y : z; 
        }

        constexpr vector4 operator-() const noexcept {
            return {-x, -y, -z, -w};
        }

        constexpr vector4& operator+=(vector4 rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;
            return *this;
        }

        constexpr vector4& operator-=(vector4 rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            z -= rhs.w;
            return *this;
        }

        constexpr vector4& operator+=(double rhs) noexcept {
            x += rhs;
            y += rhs;
            z += rhs;
            w += rhs;
            return *this;
        }

        constexpr vector4& operator-=(double rhs) noexcept {
            x -= rhs;
            y -= rhs;
            z -= rhs;
            w -= rhs;
            return *this;
        }

        constexpr vector4& operator*=(double rhs) noexcept {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            w *= rhs;
            return *this;
        }

        constexpr vector4& operator/=(double rhs) noexcept {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            w /= rhs;
            return *this;
        }

        constexpr double length_squared() const noexcept {
            return x * x + y * y + z * z;
        }

        constexpr double length() const noexcept {
            return std::sqrt(length_squared());
        }

        constexpr vector4 normalize() const noexcept {
            auto len = length();
            if (len == 0)
                return {0, 0, 0, 0};
            else
                return {x / len, y / len, z / len, w / len};
        }

        double x;
        double y;
        double z;
        double w;
    };

    constexpr inline vector4 operator+(vector4 lhs, vector4 rhs) noexcept {
        return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w};
    }

    constexpr inline vector4 operator-(vector4 lhs, vector4 rhs) noexcept {
        return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w};
    }

    constexpr inline vector4 operator+(vector4 lhs, double rhs) noexcept {
        return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs};
    }

    constexpr inline vector4 operator-(vector4 lhs, double rhs) noexcept {
        return {lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs};
    }

    constexpr inline vector4 operator*(vector4 lhs, double rhs) noexcept {
        return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs};
    }

    constexpr inline vector4 operator/(vector4 lhs, double rhs) noexcept {
        return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs};
    }
}

#endif
