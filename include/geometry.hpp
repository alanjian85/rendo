#ifndef RAYSTER_GEOMETRY_HPP
#define RAYSTER_GEOMETRY_HPP

#include <array>
#include <cstdlib>

#include "aabb.hpp"
#include "vector.hpp"
#include "vector.hpp"
#include "vertex.hpp"

namespace rayster {
    struct triangle {
        using size_type = std::size_t;

        vertex* a;
        vertex* b;
        vertex* c;

        vertex*& operator[](size_type index) {
            return index == 0 ? a : index == 1 ? b : c;
        }

        vertex* const& operator[](size_type index) const {
            return index == 0 ? a : index == 1 ? b : c;
        }

        vector3 barycentric(vector2 p) const;
        aabb2 bounding_box() const;
    };
}

#endif