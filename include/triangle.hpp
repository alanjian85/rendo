#ifndef RAYSTER_TRIANGLE_HPP
#define RAYSTER_TRIANGLE_HPP

#include <cstdlib>

#include "aabb2.hpp"
#include "vector2.hpp"
#include "vertex.hpp"

namespace rayster {
    struct triangle {
        using size_type = std::size_t;

        vertex a;
        vertex b;
        vertex c;

        vertex& operator[](size_type index) noexcept {
            return index == 0 ? a : index == 1 ? b : c;
        }

        vertex operator[](size_type index) const noexcept {
            return index == 0 ? a : index == 1 ? b : c;
        }

        vector3 barycentric(vector2 p) const noexcept;
        aabb2 bounding_box() const noexcept;
    };
}

#endif