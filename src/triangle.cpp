#include "triangle.hpp"
using namespace rayster;

#include <cmath>

aabb triangle::bounding_box() const noexcept {
    aabb res;
    res.max = vector2::min();
    res.min = vector2::max();
    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 2; ++j) {
            res.max[j] = std::max(res.max[j], (*this)[i][j]);
            res.min[j] = std::min(res.min[j], (*this)[i][j]);
        }
    }
    return res;
}