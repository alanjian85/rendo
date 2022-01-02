#ifndef RAYSTER_LOOKAT_HPP
#define RAYSTER_LOOKAT_HPP

#include "matrix4.hpp"
#include "vector3.hpp"

namespace rayster {
    class lookat : public matrix4 {
    public:
        lookat(vector3 eye, vector3 center, vector3 up) noexcept;
    };
}

#endif