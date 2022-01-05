#include "rotate.hpp"
using namespace rayster;

#include <cmath>

rotate::rotate(double angle, vector3 v) noexcept {
    auto c = std::cos(angle);
	auto s = std::sin(angle);
	auto a = v.normalize();

	(*this)(0, 0) = c + (1 - c) * a.x * a.x;
	(*this)(0, 1) = (1 - c) * a.x * a.y - s * a.z;
	(*this)(0, 2) = (1 - c) * a.x * a.z + s * a.y;
	(*this)(1, 0) = (1 - c) * a.x * a.y + s * a.z;
	(*this)(1, 1) = c + (1 - c) * a.y * a.y;
	(*this)(1, 2) = (1 - c) * a.y * a.z - s * a.x;
	(*this)(2, 0) = (1 - c) * a.x * a.z - s * a.y;
	(*this)(2, 1) = (1 - c) * a.y * a.z + s * a.x;
	(*this)(2, 2) = c + (1 - c) * a.x * a.x;
	(*this)(3, 3) = 1;
}