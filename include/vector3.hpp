#ifndef RAYSTER_VECTOR3_HPP
#define RAYSTER_VECTOR3_HPP

#include <cstdlib>
#include <cmath>

namespace rayster {
    struct vector3 { 
        vector3() 
            : x(), y(), z() 
        {
        
        }
        
        vector3(double x_, double y_, double z_) 
            : x(x_), y(y_), z(z_)
        {
            
        }

        double& operator[](std::size_t index) noexcept {
            return index == 0 ? x : index == 1 ? y : z;
        }

        const double& operator[](std::size_t index) const noexcept {
            return index == 0 ? x : index == 1 ? y : z; 
        }

        vector3 operator-() const noexcept {
            return {-x, -y, -z};
        }

        vector3& operator+=(vector3 rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        vector3& operator-=(vector3 rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        vector3& operator+=(double rhs) noexcept {
            x += rhs;
            y += rhs;
            z += rhs;
            return *this;
        }

        vector3& operator-=(double rhs) noexcept {
            x -= rhs;
            y -= rhs;
            z -= rhs;
            return *this;
        }

        vector3& operator*=(double rhs) noexcept {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }

        vector3& operator/=(double rhs) noexcept {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }

        double length_squared() const noexcept {
            return x * x + y * y + z * z;
        }

        double length() const noexcept {
            return std::sqrt(length_squared());
        }

        vector3 normalize() const noexcept {
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

    inline vector3 operator+(vector3 lhs, vector3 rhs) noexcept {
        return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
    }

    inline vector3 operator-(vector3 lhs, vector3 rhs) noexcept {
        return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
    }

    inline vector3 operator+(vector3 lhs, double rhs) noexcept {
        return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs};
    }

    inline vector3 operator-(vector3 lhs, double rhs) noexcept {
        return {lhs.x - rhs, lhs.y - rhs, lhs.z - rhs};
    }

    inline vector3 operator*(vector3 lhs, double rhs) noexcept {
        return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
    }

    inline vector3 operator/(vector3 lhs, double rhs) noexcept {
        return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
    }
}

#endif
