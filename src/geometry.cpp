#include "geometry.hpp"
using namespace rayster;

#include <cmath>

vector3 rayster::barycentric(vector2* t, vector2 p) {
    auto c = cross(
        {t[2].x - t[0].x, t[1].x - t[0].x, t[0].x - p.x},
        {t[2].y - t[0].y, t[1].y - t[0].y, t[0].y - p.y}
    );
    if (c.z == 0)
        return {-1, 1, 1};
    auto u = c.y / c.z;
    auto v = c.x / c.z;
    return {1 - u - v, u, v};
}