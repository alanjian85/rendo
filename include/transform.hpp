#ifndef RAYSTER_TRANSFORM_HPP
#define RAYSTER_TRANSFORM_HPP

#include "matrix.hpp"
#include "vector.hpp"

namespace rayster {
    matrix4 make_lookat(vector3 eye, vector3 center, vector3 up);
    matrix4 make_persp(double fov, double aspect, double near, double far);
    matrix4 make_rotate(double angle, vector3 v);
    matrix4 make_translate(vector3 offset);
}

#endif