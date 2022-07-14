#include "renderer.hpp"
using namespace box;

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>

#include "transform.hpp"

void renderer::render_triangle(triangle t, basic_shader& s) {
    s.geometry();
    
    auto aw = t[0].w;
    auto bw = t[1].w;
    auto cw = t[2].w;

    t[0] /= aw;
    t[1] /= bw;
    t[2] /= cw;

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
    auto viewport = make_viewport(0, 0, fb_.width() - 1, fb_.height() - 1);
    for (int i = 0; i < 3; ++i) {
        t[i] = viewport * t[i];
        for (int j = 0; j < 2; ++j) {
            min[j] = std::max(0, std::min<int>(min[j], static_cast<int>(t[i][j])));
            max[j] = std::min(clamp[j], std::max<int>(max[j], static_cast<int>(t[i][j])));
        }
    }

    for (auto x = min.x; x <= max.x; ++x) {
        for (auto y = min.y; y <= max.y; ++y) {
            auto bar = t.barycentric({x, y});
            if (bar.x >= 0 && bar.y >= 0 && bar.z >= 0) {
                vector3 bar_clip(bar.x / aw, bar.y / bw, bar.z / cw);
                bar_clip /= bar_clip.x + bar_clip.y + bar_clip.z;

                auto z = bar_clip.x * t[0].z + bar_clip.y * t[1].z + bar_clip.z * t[2].z;

                if (z >= 0 && z <= fb_(x, y).depth) {
                    auto color = s.frag(bar_clip);
                    if (color.has_value()) {
                        fb_(x, y).color = *color;
                        fb_(x, y).depth = z;
                    }
                }
            }
        }
    }
}

void renderer::render(int n, basic_shader& s) {    
    for (int i = 0; i < n; i += 3) {
        triangle t;
        t.a = s.vert(i);
        t.b = s.vert(i + 1);
        t.c = s.vert(i + 2);

        render_triangle(t, s);
    }
}