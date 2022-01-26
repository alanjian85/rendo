#include "matrix.hpp"
using namespace box;

matrix4 box::operator*(matrix4 lhs, matrix4 rhs) {
    matrix4 res;
    for (auto i = 0; i < 4; ++i) {
        for (auto j = 0; j < 4; ++j) {
            res(i, j) = 0;
            for (auto k = 0; k < 4; ++k) {
                res(i, j) += lhs(i, k) * rhs(k, j);
            }
        }
    }
    return res;
}

vector4 box::operator*(matrix4 lhs, vector4 rhs) {
    return {
        lhs[0][0] * rhs[0] + lhs[1][0] * rhs[1] + lhs[2][0] * rhs[2] + lhs[3][0] * rhs[3],
        lhs[0][1] * rhs[0] + lhs[1][1] * rhs[1] + lhs[2][1] * rhs[2] + lhs[3][1] * rhs[3],
        lhs[0][2] * rhs[0] + lhs[1][2] * rhs[1] + lhs[2][2] * rhs[2] + lhs[3][2] * rhs[3],
        lhs[0][3] * rhs[0] + lhs[1][3] * rhs[1] + lhs[2][3] * rhs[2] + lhs[3][3] * rhs[3]
    };
}

matrix3 matrix3::inverse() const {
    vector3 a(entries_[0][0], entries_[0][1], entries_[0][2]);
    vector3 b(entries_[1][0], entries_[1][1], entries_[1][2]);
    vector3 c(entries_[2][0], entries_[2][1], entries_[2][2]);

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

vector3 box::operator*(matrix3 lhs, vector3 rhs) {
    return {
        lhs[0][0] * rhs[0] + lhs[1][0] * rhs[1] + lhs[2][0] * rhs[2],
        lhs[0][1] * rhs[0] + lhs[1][1] * rhs[1] + lhs[2][1] * rhs[2],
        lhs[0][2] * rhs[0] + lhs[1][2] * rhs[1] + lhs[2][2] * rhs[2]
    };
}