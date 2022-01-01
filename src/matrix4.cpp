#include "matrix4.hpp"
using namespace rayster;

vector3 rayster::operator*(matrix4 lhs, vector3 rhs) noexcept {
    auto w = lhs(3, 0) * rhs.x + lhs(3, 1) * rhs.y + lhs(3, 2) * rhs.z;
    return {
        (lhs(0, 0) * rhs.x + lhs(0, 1) * rhs.y + lhs(0, 2) * rhs.z) / w,
        (lhs(1, 0) * rhs.x + lhs(1, 1) * rhs.y + lhs(1, 2) * rhs.z) / w,
        (lhs(2, 0) * rhs.x + lhs(2, 1) * rhs.y + lhs(2, 2) * rhs.z) / w,
    };
}

position3 rayster::operator*(matrix4 lhs, position3 rhs) noexcept {
    auto w = lhs(3, 0) * rhs.x + lhs(3, 1) * rhs.y + lhs(3, 2) * rhs.z + lhs(3, 3);
    return {
        (lhs(0, 0) * rhs.x + lhs(0, 1) * rhs.y + lhs(0, 2) * rhs.z + lhs(0, 3)) / w,
        (lhs(1, 0) * rhs.x + lhs(1, 1) * rhs.y + lhs(1, 2) * rhs.z + lhs(1, 3)) / w,
        (lhs(2, 0) * rhs.x + lhs(2, 1) * rhs.y + lhs(2, 2) * rhs.z + lhs(2, 3)) / w,
    };
}