#ifndef BOX_LIGHT_HPP
#define BOX_LIGHT_HPP

#include "color.hpp"
#include "vector.hpp"

namespace box {
    struct directional_light {
        vector3 dir = vector3(0, 0, 0);
        color_rgb ambient = color_rgb(1, 1, 1);
        color_rgb diffuse = color_rgb(1, 1, 1);
        color_rgb specular = color_rgb(1, 1, 1);
    };

    struct point_light {
        vector3 pos = vector3(0, 0, 0);
        color_rgb ambient = color_rgb(1, 1, 1);
        color_rgb diffuse = color_rgb(1, 1, 1);
        color_rgb specular = color_rgb(1, 1, 1);
        double shininess;
        double constant;
        double linear;
        double quadratic;
    };
}

#endif