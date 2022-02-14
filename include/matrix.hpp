#ifndef BOX_MATRIX_HPP
#define BOX_MATRIX_HPP

#include <cstdlib>

#include "vector.hpp"
#include "vector.hpp"

namespace box {
    template <typename T, std::size_t M, std::size_t N>
    class matrix;

    template <typename T>
    class matrix<T, 3, 3> {
    public:
        explicit matrix(matrix<T, 4, 4> m)
            : matrix(m[0][0], m[1][0], m[2][0],
                     m[0][1], m[1][1], m[2][1],
                     m[0][2], m[1][2], m[2][2])
        {

        }

        matrix(T e00, T e10, T e20,
               T e01, T e11, T e21,
               T e02, T e12, T e22)
        {
            entries_[0][0] = e00; entries_[1][0] = e10; entries_[2][0] = e20;
            entries_[0][1] = e01; entries_[1][1] = e11; entries_[2][1] = e21;
            entries_[0][2] = e02; entries_[1][2] = e12; entries_[2][2] = e22;
        }

        T* operator[](int i) {
            return entries_[i];
        }

        const T* operator[](int i) const {
            return entries_[i];
        }

        matrix transpose() const {
            return {
                entries_[0][0], entries_[0][1], entries_[0][2],
                entries_[1][0], entries_[1][1], entries_[1][2],
                entries_[2][0], entries_[2][1], entries_[2][2],
            };
        }

        matrix inverse() const {
            vector<T, 3> a(entries_[0][0], entries_[0][1], entries_[0][2]);
            vector<T, 3> b(entries_[1][0], entries_[1][1], entries_[1][2]);
            vector<T, 3> c(entries_[2][0], entries_[2][1], entries_[2][2]);

            auto r0 = cross(b, c);
            auto r1 = cross(c, a);
            auto r2 = cross(a, b);

            auto id = 1 / dot(r2, c);

            return {
                r0.x * id, r0.y * id, r0.z * id,
                r1.x * id, r1.y * id, r1.z * id,
                r2.x * id, r2.y * id, r2.z * id
            };
        }

        friend vector<T, 3> operator*(matrix lhs, vector<T, 3> rhs) {
            return {
                lhs[0][0] * rhs[0] + lhs[1][0] * rhs[1] + lhs[2][0] * rhs[2],
                lhs[0][1] * rhs[0] + lhs[1][1] * rhs[1] + lhs[2][1] * rhs[2],
                lhs[0][2] * rhs[0] + lhs[1][2] * rhs[1] + lhs[2][2] * rhs[2]
            };
        }
    private:
        T entries_[3][3];
    };

    using matrix3 = matrix<double, 3, 3>;

    template <typename T>
    class matrix<T, 4, 4> {
    public:    
        matrix(double t = 0)
            : matrix(t, 0, 0, 0,
                     0, t, 0, 0,
                     0, 0, t, 0,
                     0, 0, 0, t) 
        {

        }
        
        matrix(T e00, T e10, T e20, T e30,
               T e01, T e11, T e21, T e31,
               T e02, T e12, T e22, T e32,
               T e03, T e13, T e23, T e33)
        {
            entries_[0][0] = e00; entries_[1][0] = e10; entries_[2][0] = e20; entries_[3][0] = e30;
            entries_[0][1] = e01; entries_[1][1] = e11; entries_[2][1] = e21; entries_[3][1] = e31;
            entries_[0][2] = e02; entries_[1][2] = e12; entries_[2][2] = e22; entries_[3][2] = e32;
            entries_[0][3] = e03; entries_[1][3] = e13; entries_[2][3] = e23; entries_[3][3] = e33;
        }

        explicit matrix(matrix<T, 3, 3> m)
            : matrix(m[0][0], m[1][0], m[2][0], 0,
                     m[0][1], m[1][1], m[2][1], 0,
                     m[0][2], m[1][2], m[2][2], 0,
                     0,       0,       0,       1)
        {

        };

        T* operator[](int i) {
            return entries_[i];
        }

        const T* operator[](int i) const {
            return entries_[i];
        }

        T& operator()(int i, int j) {
            return entries_[j][i];
        }

        const T& operator()(int i, int j) const {
            return entries_[j][i];
        }

        friend matrix operator*(matrix lhs, matrix rhs) {
            matrix res;
            for (auto i = 0; i < 4; ++i) {
                for (auto j = 0; j < 4; ++j) {
                    for (auto k = 0; k < 4; ++k) {
                        res(i, j) += lhs(i, k) * rhs(k, j);
                    }
                }
            }
            return res;
        }

        friend vector<T, 4> operator*(matrix lhs, vector<T, 4> rhs) {
            vector<T, 4> res;
            for (auto i = 0; i < 4; ++i) {
                auto a = lhs(i, 0) * rhs[0];
                auto b = lhs(i, 1) * rhs[1];
                auto c = lhs(i, 2) * rhs[2];
                auto d = lhs(i, 3) * rhs[3];
                res[i] = a + b + c + d;
            }
            return res;
        }
    private:
        T entries_[4][4];
    };

    using matrix4 = matrix<double, 4, 4>;
}

#endif