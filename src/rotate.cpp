#include "rotate.hpp"
using namespace rayster;

#include <cmath>

rotate::rotate(double angle, unit_vector3 v) noexcept {
    auto c = std::cos(angle);
	auto s = std::sin(angle);

	(*this)(0, 0) = c + (1 - c) * v.x * v.x;
	(*this)(0, 1) = (1 - c) * v.x * v.y - s * v.z;
	(*this)(0, 2) = (1 - c) * v.x * v.z + s * v.y;
	(*this)(1, 0) = (1 - c) * v.x * v.y + s * v.z;
	(*this)(1, 1) = c + (1 - c) * v.y * v.y;
	(*this)(1, 2) = (1 - c) * v.y * v.z - s * v.x;
	(*this)(2, 0) = (1 - c) * v.x * v.z - s * v.y;
	(*this)(2, 1) = (1 - c) * v.y * v.z + s * v.x;
	(*this)(2, 2) = c + (1 - c) * v.x * v.x;
	(*this)(3, 3) = 1;
}