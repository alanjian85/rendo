#include "clip_triangle.hpp"
using namespace rayster;

#include <cmath>

aabb clip_triangle::bbox() const noexcept {
    aabb res;
    res.min = ivec2::max();
    res.max = ivec2::min();
    for (size_type i = 0; i < 3; ++i) {
        for (ivec2::size_type j = 0; j < 2; ++j) {
            res.min[j] = std::min(res.min[j], (*this)[i][j]);
            res.max[j] = std::max(res.max[j], (*this)[i][j]);
        }
    }
    return res;
}

vec3 clip_triangle::barycentric(ivec2 v) const noexcept {
    auto u = cross(vec3(c.x - a.x, b.x - a.x, a.x - v.x),
                   vec3(c.y - a.y, b.y - a.y, a.y - v.y));
    if (std::abs(u.z) < 1)
        return {-1, 1, 1};
    return {1 - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z};
}
