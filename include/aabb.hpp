#ifndef RAYSTER_AABB_HPP
#define RAYSTER_AABB_HPP

#include "vec.hpp"

namespace rayster {
    struct aabb {
        ivec2 min;
        ivec2 max;
    };
}

#endif