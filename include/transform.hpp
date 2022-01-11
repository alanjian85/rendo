#ifndef RAYSTER_TRANSFORM_HPP
#define RAYSTER_TRANSFORM_HPP

#include "matrix.hpp"
#include "vector.hpp"

namespace rayster {
    struct persp : public matrix4 {
    public:
        persp(double fov, double aspect, double near, double far) noexcept;
    };

    class rotate : public matrix4 {
    public:
        rotate(double angle, unit_vector3 v) noexcept;
    };

    class lookat : public matrix4 {
    public:
        lookat(vector3 eye, vector3 center, vector3 up) noexcept;
    };
}

#endif