#include "triangle.hpp"
using namespace rayster;

#include <cmath>

vector3 triangle::barycentric(vector2 p) const noexcept {
    auto t = cross(
        {c.pos.x - a.pos.x, b.pos.x - a.pos.x, a.pos.x - p.x},
        {c.pos.y - a.pos.y, b.pos.y - a.pos.y, a.pos.y - p.y}
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
        bbox.min.x = std::min(bbox.min.x, (*this)[i].pos.x);
        bbox.min.y = std::min(bbox.min.y, (*this)[i].pos.y);

        bbox.max.x = std::max(bbox.max.x, (*this)[i].pos.x);
        bbox.max.y = std::max(bbox.max.y, (*this)[i].pos.y);
    }
    return bbox;
}