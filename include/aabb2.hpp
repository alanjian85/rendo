#ifndef RAYSTER_AABB2_HPP
#define RAYSTER_AABB2_HPP

#include "vector2.hpp"

namespace rayster {
    struct aabb2 {
        vector2 min;
        vector2 max;
    };
}

#endif