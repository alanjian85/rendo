#ifndef RAYSTER_VIEWPORT_HPP
#define RAYSTER_VIEWPORT_HPP

#include "aabb.hpp"
#include "vector2.hpp"

namespace rayster {
    struct viewport {
        vector2 min;
        vector2 max;

        aabb bbox() const noexcept {
            return {min, max};
        }
    };
}

#endif