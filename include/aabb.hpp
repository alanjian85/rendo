#ifndef RAYSTER_AABB_HPP
#define RAYSTER_AABB_HPP

#include <cmath>

#include "vector.hpp"

namespace rayster {
    struct aabb2 {
        vector2 min;
        vector2 max;

        bool inbound(vector2 v) const {
            return v.x >= min.x && v.y >= min.y && v.x <= max.x && v.y <= max.y;
        }
    };

    inline aabb2 intersection(aabb2 lhs, aabb2 rhs) {
        return {
            {std::max(lhs.min.x, rhs.min.x), std::max(lhs.min.y, rhs.min.y)},
            {std::min(lhs.max.x, rhs.max.x), std::min(lhs.max.y, rhs.max.y)}
        };
    }
}

#endif