#include "geometry.hpp"
using namespace rayster;

#include <cmath>

vector3 triangle::barycentric(vector2i p) const {
    auto t = cross(
        vector3(c.x - a.x, b.x - a.x, a.x - p.x),
        vector3(c.y - a.y, b.y - a.y, a.y - p.y)
    );
    if (t.z == 0)
        return {-1, 1, 1};
    auto u = t.y / t.z;
    auto v = t.x / t.z;
    return {1 - u - v, u, v};
}