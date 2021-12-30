#ifndef RAYSTER_SHADER_HPP
#define RAYSTER_SHADER_HPP

#include "color.hpp"
#include "vertex_data.hpp"

namespace rayster {
    class shader {
    public:
        virtual ~shader() = default;

        virtual color_rgb fragment(const vertex_data& data) = 0;
    };
}

#endif