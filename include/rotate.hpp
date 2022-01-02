#ifndef RAYSTER_ROTATE_HPP
#define RAYSTER_ROTATE_HPP

#include "matrix4.hpp"
#include "vector3.hpp"

namespace rayster {
    class rotate : public matrix4 {
        rotate(matrix4 m) noexcept : matrix4(m) {}
    public:
        rotate(double angle, vector3 v) noexcept;
    };
}

#endif