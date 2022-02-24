#ifndef BOX_LIGHT_HPP
#define BOX_LIGHT_HPP

#include "color.hpp"
#include "transform.hpp"
#include "vector.hpp"

namespace box {
    struct directional_light {
        vector3 dir = vector3(0, 0, 0);
        color_rgb ambient = color_rgb(1, 1, 1);
        color_rgb diffuse = color_rgb(1, 1, 1);
        color_rgb specular = color_rgb(1, 1, 1);

        double left = -1;
        double right = 1;
        double bottom = -1;
        double top = 1;
        double near = 1.0;
        double far = 7.5;

        matrix4 view() {
            return make_lookat(dir, vector3(0, 0, 0), vector3(0, 1, 0));
        }

        matrix4 proj(double aspect) {
            return make_ortho(left, right, bottom, top, near, far);
        }
    };

    struct point_light {
        vector3 pos = vector3(0, 0, 0);
        color_rgb ambient = color_rgb(1, 1, 1);
        color_rgb diffuse = color_rgb(1, 1, 1);
        color_rgb specular = color_rgb(1, 1, 1);
        double constant;
        double linear;
        double quadratic;
    };
}

#endif