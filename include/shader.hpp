#ifndef RAYSTER_SHADER_HPP
#define RAYSTER_SHADER_HPP

#include "color.hpp"

namespace rayster {
    class shader {
    public:
        virtual ~shader() noexcept = default;

        virtual vector4 vert(int n) = 0;
        virtual color_rgba frag(vector3 bar) = 0;
    protected:
        template <typename T>
        static T frag_lerp(T t[3], vector3 bar) {
            return t[0] * bar.x + t[1] * bar.y + t[2] * bar.z;
        }
    };
}

#endif