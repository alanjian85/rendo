#ifndef RAYSTER_TRIANGLE_HPP
#define RAYSTER_TRIANGLE_HPP

#include <cstdlib>

#include "aabb2.hpp"
#include "vector2.hpp"
#include "vector3.hpp"

namespace rayster {
    struct triangle {
        using size_type = std::size_t;

        vector3 a;
        vector3 b;
        vector3 c;

        vector3& operator[](size_type index) noexcept {
            return index == 0 ? a : index == 1 ? b : c;
        }

        vector3 operator[](size_type index) const noexcept {
            return index == 0 ? a : index == 1 ? b : c;
        }

        vector3 barycentric(vector2 p) const noexcept;
        aabb2 bounding_box() const noexcept;
    };
}

#endif