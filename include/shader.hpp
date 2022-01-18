#ifndef RAYSTER_SHADER_HPP
#define RAYSTER_SHADER_HPP

#include "color.hpp"

namespace rayster {
    class shader {
    public:
        virtual ~shader() noexcept = default;

        virtual vector4 vert(int face, int n) = 0;
        virtual color_rgba frag(vector3 bar) = 0;
    };
}

#endif