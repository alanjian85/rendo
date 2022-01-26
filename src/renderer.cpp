#include "renderer.hpp"
using namespace box;

#include <cassert>
#include <iostream>
#include <numeric>

void renderer::render_triangle(triangle t, basic_shader& s) {
    assert(t[0].w != 0);
    assert(t[1].w != 0);
    assert(t[2].w != 0);

    auto iaw = 1 / t[0].w;
    auto ibw = 1 / t[1].w;
    auto icw = 1 / t[2].w;

    t[0] *= iaw;
    t[1] *= ibw;
    t[2] *= icw;

    auto d = dot(-vector3(t[0].x, t[0].y, t[0].z), t.normal());
    switch (face_culling_) {
        case cull_type::front:
            if (d < 0)
                return;
            break;
        case cull_type::back:
            if (d >= 0)
                return;
            break;
    }

    vector2i clamp = {
        fb_.width() - 1,
        fb_.height() - 1
    };

    vector2i min = clamp;
    vector2i max = {0, 0};
    for (int i = 0; i < 3; ++i) {
        t[i].x = (t[i].x + 1) / 2 * (fb_.width() - 1);
        t[i].y = (1 - t[i].y) / 2 * (fb_.height() - 1);

        for (int j = 0; j < 2; ++j) {
            min[j] = std::max(0, std::min(min[j], static_cast<int>(t[i][j])));
            max[j] = std::min(clamp[j], std::max(max[j], static_cast<int>(t[i][j])));
        }
    }

    for (auto x = min.x; x <= max.x; ++x) {
        for (auto y = min.y; y <= max.y; ++y) {
            auto bc_screen = t.barycentric({x, y});
            if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0)
                continue;

            auto bc_clip = vector3(bc_screen.x * iaw, bc_screen.y * ibw, bc_screen.z * icw);
            assert(bc_clip.x + bc_clip.y + bc_clip.z != 0);
            bc_clip /= bc_clip.x + bc_clip.y + bc_clip.z;

            auto z = bc_clip.x * t[0].z + bc_clip.y * t[1].z + bc_clip.z * t[2].z;

            //if (fb_.depth_test(x, y, z)) {
                auto color = s.frag(bc_clip);
                if (color.has_value()) {
                    fb_(x, y).color = *color;
                    fb_(x, y).depth = z;
                }
            //}
        }
    }
}

void renderer::render(int n, basic_shader& s) {    
    for (int i = 0; i < n; i += 3) {
        triangle t;
        t.a = s.vert(i + 0);
        t.b = s.vert(i + 1);
        t.c = s.vert(i + 2);

        render_triangle(t, s);        
    }
}