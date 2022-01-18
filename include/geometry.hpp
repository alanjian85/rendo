#ifndef RAYSTER_GEOMETRY_HPP
#define RAYSTER_GEOMETRY_HPP

#include <array>
#include <cstdlib>

#include "aabb.hpp"
#include "vector.hpp"
#include "vector.hpp"
#include "vertex.hpp"

namespace rayster {
    vector3 barycentric(vector2 p);
    aabb2 triangle_bbox();
}

#endif