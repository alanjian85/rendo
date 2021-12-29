#include "triangle.hpp"
using namespace rayster;

#include <cmath>

aabb triangle::bbox() const noexcept {
    aabb res;
    res.max = ivector2::min();
    res.min = ivector2::max();
    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 2; ++j) {
            res.max[j] = std::max(res.max[j], static_cast<int>((*this)[i][j]));
            res.min[j] = std::min(res.min[j], static_cast<int>((*this)[i][j]));
        }
    }
    return res;
}