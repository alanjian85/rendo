#include "lookat.hpp"
using namespace rayster;

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