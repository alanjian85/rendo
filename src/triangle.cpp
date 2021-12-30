#include "triangle.hpp"
using namespace rayster;

#include <cmath>

vector3 triangle::barycentric(vector2 p) const noexcept {
    auto t = cross(
        {c.x - a.x, b.x - a.x, a.x - p.x},
        {c.y - a.y, b.y - a.y, a.y - p.y}
    );
    if (t.z == 0)
        return {-1, 1, 1};
    auto u = t.x / t.z;
    auto v = t.y / t.z;
    return {1 - u - v, u, v};
}

aabb2 triangle::bounding_box() const noexcept {
    aabb2 bbox;
    bbox.min = vector2::min();
    for (auto i = 0; i < 3; ++i) {
        bbox.min.x = std::min(bbox.min.x, (*this)[i].x);
        bbox.min.y = std::min(bbox.min.y, (*this)[i].y);

        bbox.max.x = std::max(bbox.max.x, (*this)[i].x);
        bbox.max.y = std::max(bbox.max.y, (*this)[i].y);
    }
    return bbox;
}