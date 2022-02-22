#ifndef BOX_SHADER_HPP
#define BOX_SHADER_HPP

#include <optional>

#include "color.hpp"

namespace box {
    class basic_shader {
    public:
        virtual ~basic_shader() noexcept = default;

        virtual vector4 vert(int n) = 0;
        virtual void geometry() {}
        virtual std::optional<color_rgba> frag(vector3 bar, vector2 fc) = 0;
    protected:
        template <typename T>
        static T frag_lerp(T t[3], vector3 bar) {
            return t[0] * bar.x + t[1] * bar.y + t[2] * bar.z;
        }
    };
}

#endif