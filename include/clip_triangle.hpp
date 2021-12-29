#ifndef RAYSTER_CLIP_TRIANGLE_HPP
#define RAYSTER_CLIP_TRIANGLE_HPP

#include <cstdlib>

#include "aabb.hpp"
#include "vec.hpp"

namespace rayster {
    struct clip_triangle {
        using size_type = std::size_t;

        ivec2 a;
        ivec2 b;
        ivec2 c;

        aabb bbox() const noexcept;
        vec3 barycentric(ivec2 v) const noexcept;

        ivec2& operator[](size_type index) noexcept {
            return index == 0 ? a : index == 1 ? b : c;
        }

        ivec2 operator[](size_type index) const noexcept {
            return index == 0 ? a : index == 1 ? b : c;
        }
    };
}

#endif
