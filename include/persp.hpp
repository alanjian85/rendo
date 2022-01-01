#ifndef RAYSTER_PERSP_HPP
#define RAYSTER_PERSP_HPP

#include "matrix4.hpp"

namespace rayster {
    struct persp : public matrix4 {
    public:
        persp(double fov, double aspect, double near, double far) noexcept;
    };
}

#endif