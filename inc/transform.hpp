#ifndef RAYSTER_TRANSFORM_HPP
#define RAYSTER_TRANSFORM_HPP

#include "matrix.hpp"
#include "vector.hpp"

namespace rayster {
    struct persp : public matrix4 {
    public:
        persp(double fov, double aspect, double near, double far);
    };

    class rotate : public matrix4 {
    public:
        rotate(double angle, vector3 v);
    };

    class translate : public matrix4 {
    public:
        translate(vector3 offset);
    };

    class lookat : public matrix4 {
    public:
        lookat(vector3 eye, vector3 center, vector3 up);
    };
}

#endif