#ifndef RAYSTER_SHADER_HPP
#define RAYSTER_SHADER_HPP

#include "color.hpp"
#include "vertex.hpp"
#include "viewport.hpp"

namespace rayster {
    class shader {
    public:
        virtual ~shader() = default;

        virtual vertex vert(const vertex& vert) = 0;
        virtual color_rgba frag(const vertex_data& data) = 0;
    };
}

#endif