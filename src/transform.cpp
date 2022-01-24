#include "transform.hpp"
using namespace rayster;

#include <cassert>
#include <cmath>

matrix4 rayster::make_lookat(vector3 eye, vector3 center, vector3 up) {	
	auto f = (center - eye).normalize();
    auto s = cross(f, up).normalize();
    auto u = cross(s, f);

    matrix4 res;
    res(0, 0) = s.x;
	res(0, 1) = s.y;
	res(0, 2) = s.z;
	res(1, 0) = u.x;
	res(1, 1) = u.y;
	res(1, 2) = u.z;
	res(2, 0) = -f.x;
	res(2, 1) = -f.y;
	res(2, 2) = -f.z;
	res(0, 3) = -dot(s, eye);
	res(1, 3) = -dot(u, eye);
	res(2, 3) =  dot(f, eye);
	res(3, 3) = 1;
	return res;
}

matrix4 rayster::make_persp(double fov, double aspect, double near, double far) {
    auto t = std::tan(fov / 2);

	assert(t != 0);
	assert(aspect != 0);
	assert(far - near != 0);

	matrix4 res;
    res(0, 0) = 1 / (aspect * t);
    res(1, 1) = 1 / t;
    res(2, 2) = -(far + near) / (far - near);
    res(2, 3) = -(2 * far * near) / (far - near);
    res(3, 2) = -1;
	return res;
}

matrix4 rayster::make_rotate(double angle, vector3 v) {
	v = v.normalize();

    auto c = std::cos(angle);
	auto s = std::sin(angle);

	matrix4 res;
	res(0, 0) = c + (1 - c) * v.x * v.x;
	res(0, 1) = (1 - c) * v.x * v.y - s * v.z;
	res(0, 2) = (1 - c) * v.x * v.z + s * v.y;
	res(1, 0) = (1 - c) * v.x * v.y + s * v.z;
	res(1, 1) = c + (1 - c) * v.y * v.y;
	res(1, 2) = (1 - c) * v.y * v.z - s * v.x;
	res(2, 0) = (1 - c) * v.x * v.z - s * v.y;
	res(2, 1) = (1 - c) * v.y * v.z + s * v.x;
	res(2, 2) = c + (1 - c) * v.x * v.x;
	res(3, 3) = 1;
	return res;
}

matrix4 rayster::make_translate(vector3 offset) {
	matrix4 res;
	res(0, 0) = 1;
	res(0, 3) = offset.x;
	res(1, 1) = 1;
	res(1, 3) = offset.y;
	res(2, 2) = 1;
	res(2, 3) = offset.z;
	res(3, 3) = 1;
	return res;
}