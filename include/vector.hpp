#ifndef BOX_VECTOR_HPP
#define BOX_VECTOR_HPP

#include <cstdlib>
#include <cmath>
#include <limits>

namespace box {
    template <typename T, std::size_t N>
    struct vector;

    template <typename T>
    struct vector<T, 2> {
        T x, y;

        vector() = default;
        vector(T x_, T y_)
            : x(x_), y(y_)
        {

        }

        T& operator[](int i) {
            return i == 0 ? x : y;
        }

        const T& operator[](int i) const {
            return i == 0 ? x : y;
        }

        T& operator*=(T rhs) {
            x *= rhs;
            y *= rhs;
            return *this;
        }
    
        friend vector operator+(vector lhs, vector rhs) {
            return {lhs.x + rhs.x, lhs.y + rhs.y};
        }

        friend vector operator*(vector lhs, double rhs) {
            return {lhs.x * rhs, lhs.y * rhs};
        }

        friend vector operator*(double lhs, vector rhs) {
            return rhs * lhs;
        }
    };

    using vector2 = vector<double, 2>;
    using vector2i = vector<int, 2>;

    template <typename T>
    struct vector<T, 3> {
        T x, y, z;

        vector() = default;
        vector(T x_, T y_, T z_)
            : x(x_), y(y_), z(z_)
        {

        }
        explicit vector(vector<T, 4> v)
            : x(v.x), y(v.y), z(v.z)
        {

        }

        T& operator[](int i) {
            return i == 0 ? x : i == 1 ? y : z;
        }

        const T& operator[](int i) const {
            return i == 0 ? x : i == 1 ? y : z;
        }

        vector operator-() const {
            return {-x, -y, -z};
        }

        vector& operator*=(T rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }

        vector& operator/=(T rhs) {
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

        vector normalize() const {
            auto len = length();
            if (len == 0)
                return {0, 0, 0};
            return {x / len, y / len, z / len};
        }
    
        friend vector operator+(vector lhs, vector rhs) {
            return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
        }

        friend vector operator-(vector lhs, vector rhs) {
            return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
        }

        friend vector operator*(vector lhs, double rhs) {
            return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
        }

        friend vector operator*(double lhs, vector rhs) {
            return rhs * lhs;
        }

        friend double dot(vector lhs, vector rhs) {
            return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
        }

        friend vector cross(vector lhs, vector rhs) {
            return {
                lhs.y * rhs.z - lhs.z * rhs.y,
                lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.x * rhs.y - lhs.y * rhs.x
            };
        }

        friend vector reflect(vector i, vector n) {
            return i - 2 * dot(n, i) * n;
        }
    };

    using vector3 = vector<double, 3>;
    
    template <typename T>
    struct vector<T, 4> {
        T x, y, z, w;

        vector() = default;
        vector(T x_, T y_, T z_, T w_)
            : x(x_), y(y_), z(z_), w(w_)
        {

        }
        vector(vector<T, 3> v, T w_) 
            : x(v.x), y(v.y), z(v.z), w(w_)
        {

        }
    
        T& operator[](int i) {
            return i == 0 ? x : i == 1 ? y : i == 2 ? z : w;
        }

        const T& operator[](int i) const {
            return i == 0 ? x : i == 1 ? y : i == 2 ? z : w;
        }

        vector& operator*=(T rhs) {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            w *= rhs;
            return *this;
        }

        friend vector operator+(vector lhs, vector rhs) {
            return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w};
        }
    };

    using vector4 = vector<double, 4>;
}

#endif