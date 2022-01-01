#ifndef RAYSTER_UTILITY_HPP

namespace rayster {
    constexpr auto pi = 3.14159;

    constexpr auto inline rad(double deg) noexcept {
        return deg * pi / 180;
    }
}

#endif