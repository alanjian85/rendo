#ifndef RAYSTER_VECTOR2_HPP
#define RAYSTER_VECTOR2_HPP

namespace rayster {
    struct vector2 {
        double x;
        double y;

        static vector2 min() noexcept;
        static vector2 max() noexcept;
    };
}

#endif