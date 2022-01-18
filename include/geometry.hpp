#ifndef RAYSTER_GEOMETRY_HPP
#define RAYSTER_GEOMETRY_HPP

#include <array>
#include <cstdlib>

#include "vector.hpp"

namespace rayster {
    struct triangle {
        using size_type = int;

        vector3 a;
        vector3 b;
        vector3 c;
    
        vector3& operator[](size_type i) {

        }

        vector3 barycentric(vector2 p) const;
    };
}

#endif