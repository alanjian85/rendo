#include "rotate.hpp"
using namespace rayster;

#include <cmath>

rotate::rotate(double angle, vector3 v) noexcept {
    auto c = std::cos(angle);
    auto s = std::sin(angle);

    auto axis = v.normalize();
    auto temp = (1 - c) * axis;

	(*this)(0, 0) = c + temp.x * axis.x;
	(*this)(1, 0) = temp.x * axis.y + s * axis.z;
	(*this)(2, 0) = temp.x * axis.z - s * axis.y;

	(*this)(0, 1) = temp.y * axis.x - s * axis.z;
	(*this)(1, 1) = c + temp.y * axis.y;
	(*this)(2, 1) = temp.y * axis.z + s * axis.x;

	(*this)(0, 2) = temp.z * axis.x + s * axis.y;
	(*this)(1, 2) = temp.z * axis.y - s * axis.x;
	(*this)(2, 2) = c + temp.z * axis.z;
    
    *this = transpose();
}