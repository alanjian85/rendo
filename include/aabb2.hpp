#ifndef RAYSTER_AABB2_HPP
#define RAYSTER_AABB2_HPP

#include "vector2.hpp"

namespace rayster {
    struct aabb2 {
        vector2 min;
        vector2 max;

        bool inbound(vector2 v) const noexcept {
            return v.x >= min.x && v.y >= min.y && v.x <= max.x && v.y <= max.y;
        }
    };
}

#endif