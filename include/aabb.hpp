#ifndef RAYSTER_AABB_HPP
#define RAYSTER_AABB_HPP

#include "ivector2.hpp"

namespace rayster {
    struct aabb {
        ivector2 min;
        ivector2 max;

        bool inbound(ivector2 v) const noexcept {
            return v.x >= min.x && v.x <= max.x &&
                   v.y >= min.y && v.y <= max.y;
        }
    };
}

#endif