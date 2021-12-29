#ifndef RAYSTER_AABB_HPP
#define RAYSTER_AABB_HPP

#include "vector2.hpp"

namespace rayster {
    struct aabb {
        vector2 min;
        vector2 max;

        bool inbound(vector2 v) const noexcept {
            return v.x >= min.x && v.x <= max.x &&
                   v.y >= min.y && v.y <= max.y;
        }
    };
}

#endif