#ifndef BOX_GEOMETRY_HPP
#define BOX_GEOMETRY_HPP

#include <array>
#include <cstdlib>

#include "vector.hpp"

namespace box {
    struct triangle {
        using size_type = int;

        vector4 a;
        vector4 b;
        vector4 c;
    
        vector4& operator[](size_type i) {
            return i == 0 ? a : i == 1 ? b : c;
        }

        const vector4& operator[](size_type i) const {
            return i == 0 ? a : i == 1 ? b : c;
        }

        vector3 normal() const {
            return cross(
                vector3(b.x - a.x, b.y - a.y, b.z - a.z),
                vector3(c.x - a.x, c.y - a.y, c.z - a.z)
            );
        }

        vector3 barycentric(vector2i p) const;
    };
}

#endif