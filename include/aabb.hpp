#ifndef RAYSTER_AABB_HPP
#define RAYSTER_AABB_HPP

#include "vec.hpp"

namespace rayster {
    struct aabb {
        ivec2 min;
        ivec2 max;

        bool inbound(ivec2 v) const noexcept {
            return v.x >= min.x && v.x <= max.x &&
                   v.y >= min.y && v.y <= max.y;
        }
    };
}

#endif