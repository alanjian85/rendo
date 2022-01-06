#ifndef RAYSTER_VECTOR4_HPP
#define RAYSTER_VECTOR4_HPP

namespace rayster {
    struct vector4 {
        double x;
        double y;
        double z;
        double w;
    
        vector4& operator*=(double rhs) noexcept {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            w *= rhs;
            return *this;
        }
    };
}

#endif