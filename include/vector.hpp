#ifndef RAYSTER_VECTOR_HPP
#define RAYSTER_VECTOR_HPP

#include <cmath>
#include <limits>

namespace rayster {
    struct vector2 {
        using size_type = int;

        double x;
        double y;

        double& operator[](size_type i) {
            return i == 0 ? x : y;
        }

        const double& operator[](size_type i) const {
            return i == 0 ? x : y;
        }

        vector2& operator*=(double rhs) {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        static vector2 min() {
            return {
                std::numeric_limits<double>::min(),
                std::numeric_limits<double>::min()
            };
        }

        static vector2 max() {
            return {
                std::numeric_limits<double>::max(),
                std::numeric_limits<double>::max()
            };
        }
    };

    inline vector2 operator+(vector2 lhs, vector2 rhs) {
        return {lhs.x + rhs.x, lhs.y + rhs.y};
    }

    inline vector2 operator*(vector2 lhs, double rhs) {
        return {lhs.x * rhs, lhs.y * rhs};
    }

    inline vector2 operator*(double lhs, vector2 rhs) {
        return rhs * lhs;
    }

    struct vector3 {
        using size_type = int;

        double x;
        double y;
        double z;

        double& operator[](size_type i) {
            return i == 0 ? x : i == 1 ? y : z;
        }

        const double& operator[](size_type i) const {
            return i == 0 ? x : i == 1 ? y : z;
        }

        vector3& operator*=(double rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }

        auto length_squared() const {
            return x * x + y * y + z * z;
        }

        auto length() const {
            return std::sqrt(length_squared());
        }

        vector3 normalize() const {
            auto len = length();
            if (len == 0)
                return {0, 0, 0};
            return {x / len, y / len, z / len};
        }
    };

    inline vector3 operator+(vector3 lhs, vector3 rhs) {
        return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
    }

    inline vector3 operator-(vector3 lhs, vector3 rhs) {
        return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
    }

    inline vector3 operator*(vector3 lhs, double rhs) {
        return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
    }

    inline vector3 operator*(double lhs, vector3 rhs) {
        return rhs * lhs;
    }

    inline double dot(vector3 lhs, vector3 rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    inline vector3 cross(vector3 lhs, vector3 rhs) {
        return {
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x
        };
    }
    
    struct vector4 {
        double x;
        double y;
        double z;
        double w;
    
        vector4& operator*=(double rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            w *= rhs;
            return *this;
        }
    };
}

#endif