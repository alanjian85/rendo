#include "renderer.hpp"
using namespace box;

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>

void renderer::render_triangle(triangle t, basic_shader& s) {
    s.geometry();
    
    for (int i = 0; i < 3; ++i) {
        t[i].x /= t[i].w;
        t[i].y /= t[i].w;
        t[i].z /= t[i].w;
    }

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
        t[i].x = static_cast<int>(0.5 * (fb_.width() - 1) * (t[i].x + 1));
        t[i].y = static_cast<int>(0.5 * (fb_.height() - 1) * (1 - t[i].y));

        for (int j = 0; j < 2; ++j) {
            min[j] = std::max(0, std::min<int>(min[j], t[i][j]));
            max[j] = std::min(clamp[j], std::max<int>(max[j], t[i][j]));
        }
    }

    for (auto x = min.x; x <= max.x; ++x) {
        for (auto y = min.y; y <= max.y; ++y) {
            auto bar = t.barycentric({x, y});
            if (bar.x >= 0 && bar.y >= 0 && bar.z >= 0) {
                vector3 bar_clip(bar.x / t[0].w, bar.y / t[1].w, bar.z / t[2].w);
                bar_clip /= bar_clip.x + bar_clip.y + bar_clip.z;

                auto z = bar_clip.x * t[0].z + bar_clip.y * t[1].z + bar_clip.z * t[2].z;

                if (z > -1 && z < fb_(x, y).depth) {
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

void renderer::post_process(const post_processor_type& p) {
    for (int y = 0; y < fb_.height(); --y) {
        for (int x = 0; x < fb_.width(); --x) {
            vector2 fc;
            fc.x = static_cast<double>(x) / (fb_.width() - 1);
            fc.y = static_cast<double>(y) / (fb_.height() - 1);
            fb_(x, y).color = p(fc, fb_(x, y));
        }
    }
}