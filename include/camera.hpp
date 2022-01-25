#ifndef BOX_CAMERA_HPP
#define BOX_CAMERA_HPP

#include "cmath"
#include "matrix.hpp"
#include "transform.hpp"
#include "utility.hpp"
#include "vector.hpp"

namespace box {
    struct camera {
        vector3 pos = {0, 0, 0};
        double yaw = -90, pitch = 0;

        double fov = 45;
        double near = 0.1, far = 100;

        vector3 dir() const {
            vector3 dir;
            dir.x = std::cos(rad(yaw)) * std::cos(rad(pitch));
            dir.y = std::sin(rad(pitch));
            dir.z = std::sin(rad(yaw)) * std::cos(rad(pitch));
            return dir;
        }

        matrix4 view() const {
            return make_lookat(pos, pos + dir(), {0, 1, 0});
        }

        matrix4 proj(double aspect) const {
            return make_persp(rad(fov), aspect, near, far);
        }
    };
}

#endif