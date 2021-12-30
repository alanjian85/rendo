#ifndef RAYSTER_VIEWPORT_HPP
#define RAYSTER_VIEWPORT_HPP

#include "aabb2.hpp"
#include "vector2.hpp"

namespace rayster {
    struct viewport {
        vector2 min;
        vector2 max;
        
        aabb2 bounding_box() const noexcept {
            return {
                min,
                {max.x - 1, max.y - 1}
            };
        }
    };
}

#endif