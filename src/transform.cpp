#include "transform.hpp"
using namespace box;

#include <cassert>
#include <cmath>

matrix4 box::make_persp(double fov, double aspect, double near, double far) {
    auto t = std::tan(fov / 2);

	matrix4 m;
    m(0, 0) = 1 / (aspect * t);
    m(1, 1) = 1 / t;
    m(2, 2) = -(far + near) / (far - near);
    m(2, 3) = -(2 * far * near) / (far - near);
    m(3, 2) = -1;
	return m;
}

matrix4 box::make_lookat(vector3 eye, vector3 center, vector3 up) {
    auto f = (center - eye).normalize();
    auto s = cross(f, up).normalize();
    auto u = cross(s, f);

	matrix4 m(1);
    m(0, 0) = s.x;
	m(0, 1) = s.y;
	m(0, 2) = s.z;
	m(1, 0) = u.x;
	m(1, 1) = u.y;
	m(1, 2) = u.z;
	m(2, 0) = -f.x;
	m(2, 1) = -f.y;
	m(2, 2) = -f.z;
	m(0, 3) = -dot(s, eye);
	m(1, 3) = -dot(u, eye);
	m(2, 3) =  dot(f, eye);
	return m;
}

matrix4 box::make_translate(vector3 offset) {
	matrix4 m(1);
	m(0, 3) = offset.x;
	m(1, 3) = offset.y;
	m(2, 3) = offset.z;
	return m;
}

matrix4 box::make_rotate(double angle, vector3 v) {
	v = v.normalize();

    auto c = std::cos(angle);
	auto s = std::sin(angle);

	matrix4 m(1);
	m(0, 0) = c + (1 - c) * v.x * v.x;
	m(0, 1) = (1 - c) * v.x * v.y - s * v.z;
	m(0, 2) = (1 - c) * v.x * v.z + s * v.y;
	m(1, 0) = (1 - c) * v.x * v.y + s * v.z;
	m(1, 1) = c + (1 - c) * v.y * v.y;
	m(1, 2) = (1 - c) * v.y * v.z - s * v.x;
	m(2, 0) = (1 - c) * v.x * v.z - s * v.y;
	m(2, 1) = (1 - c) * v.y * v.z + s * v.x;
	m(2, 2) = c + (1 - c) * v.x * v.x;
	return m;
}