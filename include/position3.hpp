#ifndef RAYSTER_POSITION3_HPP
#define RAYSTER_POSITION3_HPP

#include <iostream>

namespace rayster {
    struct position3 {
        double x;
        double y;
        double z;
    };

    inline std::ostream& operator<<(std::ostream& lhs, position3 rhs) noexcept {
        lhs << '(' << rhs.x << ' ' << rhs.y << ' ' << rhs.z << ')';
        return lhs;
    }
}

#endif