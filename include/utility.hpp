#ifndef BOX_UTILITY_HPP
#define BOX_UTILITY_HPP

namespace box {
    constexpr auto pi = 3.14159;

    constexpr auto rad(double deg) {
        return deg * pi / 180;
    }
}

#endif