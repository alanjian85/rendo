#include "clip_triangle.hpp"
using namespace rayster;

#include <cmath>

aabb clip_triangle::bbox() const noexcept {
    aabb res;
    res.min = ivec2::max();
    res.max = ivec2::min();
    for (auto v : *this) {
        for (ivec2::size_type i = 0; i < 2; ++i) {
            res.min[i] = std::min(res.min[i], v[i]);
            res.max[i] = std::max(res.max[i], v[i]);
        }
    }
    return res;
}