#ifndef BOX_VECTOR_HPP
#define BOX_VECTOR_HPP

#include <cmath>
#include <limits>

namespace box {
    template <typename T>
    struct basic_vector2 {
        using size_type = int;

        T x, y;

        basic_vector2() = default;
        basic_vector2(T x_, T y_)
            : x(x_), y(y_)
        {

        }

        T& operator[](size_type i) {
            return i == 0 ? x : y;
        }

        const T& operator[](size_type i) const {
            return i == 0 ? x : y;
        }

        T& operator*=(T rhs) {
            x *= rhs;
            y *= rhs;
            return *this;
        }
    
        friend basic_vector2 operator+(basic_vector2 lhs, basic_vector2 rhs) {
            return {lhs.x + rhs.x, lhs.y + rhs.y};
        }

        friend basic_vector2 operator*(basic_vector2 lhs, double rhs) {
            return {lhs.x * rhs, lhs.y * rhs};
        }

        friend basic_vector2 operator*(double lhs, basic_vector2 rhs) {
            return rhs * lhs;
        }
    };

    using vector2 = basic_vector2<double>;
    using vector2i = basic_vector2<int>;

    template <typename T>
    struct basic_vector3 {
        using size_type = int;

        T x, y, z;

        basic_vector3() = default;
        basic_vector3(T x_, T y_, T z_)
            : x(x_), y(y_), z(z_)
        {

        }

        T& operator[](size_type i) {
            return i == 0 ? x : i == 1 ? y : z;
        }

        const T& operator[](size_type i) const {
            return i == 0 ? x : i == 1 ? y : z;
        }

        basic_vector3& operator*=(T rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }

        basic_vector3& operator/=(T rhs) {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }

        auto length_squared() const {
            return x * x + y * y + z * z;
        }

        auto length() const {
            return std::sqrt(length_squared());
        }

        basic_vector3 normalize() const {
            auto len = length();
            if (len == 0)
                return {0, 0, 0};
            return {x / len, y / len, z / len};
        }
    
        friend basic_vector3 operator+(basic_vector3 lhs, basic_vector3 rhs) {
            return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
        }

        friend basic_vector3 operator-(basic_vector3 lhs, basic_vector3 rhs) {
            return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
        }

        friend basic_vector3 operator*(basic_vector3 lhs, double rhs) {
            return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
        }

        friend basic_vector3 operator*(double lhs, basic_vector3 rhs) {
            return rhs * lhs;
        }

        friend double dot(basic_vector3 lhs, basic_vector3 rhs) {
            return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
        }

        friend basic_vector3 cross(basic_vector3 lhs, basic_vector3 rhs) {
            return {
                lhs.y * rhs.z - lhs.z * rhs.y,
                lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.x * rhs.y - lhs.y * rhs.x
            };
        }
    };

    using vector3 = basic_vector3<double>;
    
    template <typename T>
    struct basic_vector4 {
        using size_type = int;

        T x, y, z, w;

        basic_vector4() = default;
        basic_vector4(T x_, T y_, T z_, T w_)
            : x(x_), y(y_), z(z_), w(w_)
        {

        }
    
        T& operator[](size_type i) {
            return i == 0 ? x : i == 1 ? y : i == 2 ? z : w;
        }

        const T& operator[](size_type i) const {
            return i == 0 ? x : i == 1 ? y : i == 2 ? z : w;
        }

        basic_vector4& operator*=(T rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            w *= rhs;
            return *this;
        }
    };

    using vector4 = basic_vector4<double>;
}

#endif