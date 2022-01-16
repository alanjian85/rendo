#ifndef RAYSTER_UTILITY_HPP

namespace rayster {
    constexpr auto pi = 3.14159;

    constexpr auto rad(double deg) {
        return deg * pi / 180;
    }
}

#endif