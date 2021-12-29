#ifndef RAYSTER_TRIANGLE_HPP
#define RAYSTER_TRIANGLE_HPP

#include "vector3.hpp"

#include "aabb.hpp"

namespace rayster {
    struct triangle {
        vector3 a;
        vector3 b;
        vector3 c;

        vector3& operator[](std::size_t index) noexcept {
            return index == 0 ? a : index == 1 ? b : c;
        }

        const vector3& operator[](std::size_t index) const noexcept {
            return index == 0 ? a : index == 1 ? b : c;
        }

        aabb bounding_box() const noexcept;
    };
}

#endif