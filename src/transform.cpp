#include "transform.hpp"
using namespace rayster;

#include <cmath>

lookat::lookat(vector3 eye, vector3 center, vector3 up) noexcept {
    auto f = (center - eye).normalize();
    auto s = cross(up, f).normalize();
    auto u = cross(f, s);

    (*this)(0, 0) = s.x;
	(*this)(0, 1) = s.y;
	(*this)(0, 2) = s.z;
	(*this)(1, 0) = u.x;
	(*this)(1, 1) = u.y;
	(*this)(1, 2) = u.z;
	(*this)(2, 0) = f.x;
	(*this)(2, 1) = f.y;
	(*this)(2, 2) = f.z;
	(*this)(0, 3) = -dot(s, eye);
	(*this)(1, 3) = -dot(u, eye);
	(*this)(2, 3) = -dot(f, eye);
	(*this)(3, 3) = 1;
}

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

persp::persp(double fov, double aspect, double near, double far) noexcept {
    auto t = std::tan(fov / 2);

    (*this)(0, 0) = 1 / (aspect * t);
    (*this)(1, 1) = 1 / t;
    (*this)(2, 2) = (far + near) / (far - near);
    (*this)(2, 3) = -(2 * far * near) / (far - near);
    (*this)(3, 2) = 1;
}