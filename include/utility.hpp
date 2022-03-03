#ifndef BOX_UTILITY_HPP
#define BOX_UTILITY_HPP

#include <algorithm>

namespace box {
    constexpr auto pi = 3.14159;

    constexpr auto rad(double deg) {
        return deg * pi / 180;
    }

    constexpr auto lerp(double min, double max, double val) {
        return min + val * (max - min);
    }

    constexpr auto smoothstep(double edge0, double edge1, double x) {
        auto t = std::clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
        return t * t * (3.0 - 2.0 * t);
    }
}

#endif