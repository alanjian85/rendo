#ifndef RAYSTER_GEOMETRY_HPP
#define RAYSTER_GEOMETRY_HPP

#include <array>
#include <cstdlib>

#include "vector.hpp"
#include "vector.hpp"

namespace rayster {
    vector3 barycentric(vector2* t, vector2 p);
}

#endif