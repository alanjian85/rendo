#ifndef RAYSTER_ROTATE_HPP
#define RAYSTER_ROTATE_HPP

#include "matrix4.hpp"
#include "vector.hpp"

namespace rayster {
    class rotate : public matrix4 {
    public:
        rotate(double angle, unit_vector3 v) noexcept;
    };
}

#endif