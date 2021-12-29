#ifndef RAYSTER_AABB_HPP
#define RAYSTER_AABB_HPP

#include "vector2.hpp"

namespace rayster {
    struct aabb {
        vector2 min;
        vector2 max;
    };
}

#endif