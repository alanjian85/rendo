#ifndef BOX_LIGHT_HPP
#define BOX_LIGHT_HPP

#include "color.hpp"
#include "vector.hpp"

namespace box {
    struct directional_light {
        vector3 dir;
        color_rgb ambient;
        color_rgb diffuse;
        color_rgb specular;
    };

    struct point_light {
        vector3 pos;
        color_rgb ambient;
        color_rgb diffuse;
        color_rgb specular;
        double shininess;
        double constant;
        double linear;
        double quadratic;
    };
}

#endif