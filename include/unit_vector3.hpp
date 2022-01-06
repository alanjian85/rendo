#ifndef RAYSTER_UNIT_VECTOR3_HPP
#define RAYSTER_UNIT_VECTOR3_HPP

#include <cmath>

#include "vector3.hpp"

namespace rayster {
    struct unit_vector3 {
        double x;
        double y;
        double z;

        unit_vector3(double x_, double y_, double z_) noexcept {
            auto len = std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
            if (len == 0) {
                x = 0;
                y = 0;
                z = 0;
                return;
            }

            x = x_ / len;
            y = y_ / len;
            z = z_ / len;
        }

        unit_vector3(vector3 rhs) noexcept
            : unit_vector3(rhs.x, rhs.y, rhs.z)
        {

        }
    };
}

#endif