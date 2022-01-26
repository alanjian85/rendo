#ifndef BOX_MATRIX_HPP
#define BOX_MATRIX_HPP

#include <cstdlib>

#include "vector.hpp"
#include "vector.hpp"

namespace box {
    class matrix4 {
    public:    
        matrix4()
            : matrix4(1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1) 
        {

        }
        
        matrix4(double e00, double e01, double e02, double e03,
                double e10, double e11, double e12, double e13,
                double e20, double e21, double e22, double e23,
                double e30, double e31, double e32, double e33)
        {
            entries_[0][0] = e00; entries_[0][1] = e10; entries_[0][2] = e20; entries_[0][3] = e30;
            entries_[1][0] = e01; entries_[1][1] = e11; entries_[1][2] = e21; entries_[1][3] = e31;
            entries_[2][0] = e02; entries_[2][1] = e12; entries_[2][2] = e22; entries_[2][3] = e32;
            entries_[3][0] = e03; entries_[3][1] = e13; entries_[3][2] = e23; entries_[3][3] = e33;
        }

        double& operator()(int i, int j) {
            return entries_[j][i];
        }

        const double& operator()(int i, int j) const {
            return entries_[j][i];
        }

        double* operator[](int i) {
            return entries_[i];
        }

        const double* operator[](int i) const {
            return entries_[i];
        }
    private:
        double entries_[4][4];
    };

    matrix4 operator*(matrix4 lhs, matrix4 rhs);
    vector4 operator*(matrix4 lhs, vector4 rhs);

    class matrix3 {
    public:
        explicit matrix3(matrix4 m) 
            : matrix3(m[0][0], m[1][0], m[2][0],
                      m[0][1], m[1][1], m[2][1],
                      m[0][2], m[1][2], m[2][2])
        {

        }

        matrix3(double e00, double e01, double e02,
                double e10, double e11, double e12,
                double e20, double e21, double e22)
        {
            entries_[0][0] = e00; entries_[0][1] = e10; entries_[0][2] = e20;
            entries_[1][0] = e01; entries_[1][1] = e11; entries_[1][2] = e21;
            entries_[2][0] = e02; entries_[2][1] = e12; entries_[2][2] = e22;
        }

        double* operator[](int i) {
            return entries_[i];
        }

        const double* operator[](int i) const {
            return entries_[i];
        }

        matrix3 transpose() const {
            return {
                entries_[0][0], entries_[0][1], entries_[0][2],
                entries_[1][0], entries_[1][1], entries_[1][2],
                entries_[2][0], entries_[2][1], entries_[2][2],
            };
        }

        matrix3 inverse() const;
    private:
        double entries_[3][3];
    };

    vector3 operator*(matrix3 lhs, vector3 rhs);
}

#endif