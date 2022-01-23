#ifndef RAYSTER_GEOMETRY_HPP
#define RAYSTER_GEOMETRY_HPP

#include <array>
#include <cstdlib>

#include "vector.hpp"

namespace rayster {
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

        vector3 barycentric(vector2 p) const;
    };
}

#endif