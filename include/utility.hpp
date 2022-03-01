#ifndef BOX_UTILITY_HPP
#define BOX_UTILITY_HPP

namespace box {
    constexpr auto pi = 3.14159;

    constexpr auto rad(double deg) {
        return deg * pi / 180;
    }

    constexpr auto lerp(double min, double max, double val) {
        return min + val * (max - min);
    }
}

#endif