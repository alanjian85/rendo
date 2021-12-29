#ifndef RAYSTER_VECTOR3_HPP
#define RAYSTER_VECTOR3_HPP

#include <cstdlib>
#include <cmath>

namespace rayster {
    struct vector3 { 
        constexpr vector3() 
            : x(), y(), z() 
        {
        
        }
        constexpr vector3(double x_, double y_, double z_) 
            : x(x_), y(y_), z(z_)
        {
            
        }

        constexpr double& operator[](std::size_t index) noexcept {
            return index == 0 ? x : index == 1 ? y : z;
        }

        constexpr const double& operator[](std::size_t index) const noexcept {
            return index == 0 ? x : index == 1 ? y : z; 
        }

        constexpr vector3 operator-() const noexcept {
            return {-x, -y, -z};
        }

        constexpr vector3& operator+=(vector3 rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        constexpr vector3& operator-=(vector3 rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        constexpr vector3& operator+=(double rhs) noexcept {
            x += rhs;
            y += rhs;
            z += rhs;
            return *this;
        }

        constexpr vector3& operator-=(double rhs) noexcept {
            x -= rhs;
            y -= rhs;
            z -= rhs;
            return *this;
        }

        constexpr vector3& operator*=(double rhs) noexcept {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }

        constexpr vector3& operator/=(double rhs) noexcept {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }

        constexpr double length_squared() const noexcept {
            return x * x + y * y + z * z;
        }

        constexpr double length() const noexcept {
            return std::sqrt(length_squared());
        }

        constexpr vector3 normalize() const noexcept {
            auto len = length();
            if (len == 0)
                return {0, 0, 0};
            else
                return {x / len, y / len, z / len};
        }

        double x;
        double y;
        double z;
    };

    constexpr inline vector3 operator+(vector3 lhs, vector3 rhs) noexcept {
        return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
    }

    constexpr inline vector3 operator-(vector3 lhs, vector3 rhs) noexcept {
        return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
    }

    constexpr inline vector3 operator+(vector3 lhs, double rhs) noexcept {
        return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs};
    }

    constexpr inline vector3 operator-(vector3 lhs, double rhs) noexcept {
        return {lhs.x - rhs, lhs.y - rhs, lhs.z - rhs};
    }

    constexpr inline vector3 operator*(vector3 lhs, double rhs) noexcept {
        return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
    }

    constexpr inline vector3 operator/(vector3 lhs, double rhs) noexcept {
        return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
    }
}

#endif
