#ifndef RAYSTER_VECTOR3_HPP
#define RAYSTER_VECTOR3_HPP

namespace rayster {
    struct vector3 {
        double x;
        double y;
        double z;
    };

    inline vector3 cross(vector3 lhs, vector3 rhs) noexcept {
        return {
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x
        };
    }
}

#endif