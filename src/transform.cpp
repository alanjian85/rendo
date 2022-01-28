#include "transform.hpp"
using namespace box;

#include <cassert>
#include <cmath>

matrix4 box::make_lookat(vector3 eye, vector3 center, vector3 up) {	
	auto f = (eye - center).normalize();
    auto s = cross(up, f).normalize();
    auto u = cross(f, s);

    matrix4 res(1);
    res[0][0] = s.x;
	res[1][0] = s.y;
	res[2][0] = s.z;
	res[0][1] = u.x;
	res[1][1] = u.y;
	res[2][1] = u.z;
	res[0][2] = f.x;
	res[1][2] = f.y;
	res[2][2] = f.z;
	res[3][0] = -dot(s, eye);
	res[3][1] = -dot(u, eye);
	res[3][2] = -dot(f, eye);
	return res;
}

matrix4 box::make_persp(double fov, double aspect, double near, double far) {
    auto t = std::tan(fov / 2);

	matrix4 res;
    res[0][0] = 1 / (aspect * t);
    res[1][1] = 1 / t;
    res[2][2] = -(far + near) / (far - near);
    res[2][3] = -1;
    res[3][2] = -(2 * far * near) / (far - near);
	return res;
}

matrix4 box::make_rotate(double angle, vector3 v) {
	v = v.normalize();

    auto c = std::cos(angle);
	auto s = std::sin(angle);

	matrix4 res(1);
	res[0][0] = c + (1 - c) * v.x * v.x;
	res[1][0] = (1 - c) * v.x * v.y - s * v.z;
	res[2][0] = (1 - c) * v.x * v.z + s * v.y;
	res[0][1] = (1 - c) * v.x * v.y + s * v.z;
	res[1][1] = c + (1 - c) * v.y * v.y;
	res[2][1] = (1 - c) * v.y * v.z - s * v.x;
	res[0][2] = (1 - c) * v.x * v.z - s * v.y;
	res[1][2] = (1 - c) * v.y * v.z + s * v.x;
	res[2][2] = c + (1 - c) * v.x * v.x;
	return res;
}

matrix4 box::make_translate(vector3 offset) {
	matrix4 res(1);
	res[3][0] = offset.x;
	res[3][1] = offset.y;
	res[3][2] = offset.z;
	return res;
}