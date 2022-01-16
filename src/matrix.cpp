#include "matrix.hpp"
using namespace rayster;

matrix4 rayster::operator*(matrix4 lhs, matrix4 rhs) {
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

vector4 rayster::operator*(matrix4 lhs, vector4 rhs) {
    return {
        lhs(0, 0) * rhs.x + lhs(0, 1) * rhs.y + lhs(0, 2) * rhs.z + lhs(0, 3) * rhs.w,
        lhs(1, 0) * rhs.x + lhs(1, 1) * rhs.y + lhs(1, 2) * rhs.z + lhs(1, 3) * rhs.w,
        lhs(2, 0) * rhs.x + lhs(2, 1) * rhs.y + lhs(2, 2) * rhs.z + lhs(2, 3) * rhs.w,
        lhs(3, 0) * rhs.x + lhs(3, 1) * rhs.y + lhs(3, 2) * rhs.z + lhs(3, 3) * rhs.w
    };
}

vector3 rayster::operator*(matrix4 lhs, vector3 rhs) {
    auto w = lhs(3, 0) * rhs.x + lhs(3, 1) * rhs.y + lhs(3, 2) * rhs.z;
    return {
        (lhs(0, 0) * rhs.x + lhs(0, 1) * rhs.y + lhs(0, 2) * rhs.z) / w,
        (lhs(1, 0) * rhs.x + lhs(1, 1) * rhs.y + lhs(1, 2) * rhs.z) / w,
        (lhs(2, 0) * rhs.x + lhs(2, 1) * rhs.y + lhs(2, 2) * rhs.z) / w,
    };
}