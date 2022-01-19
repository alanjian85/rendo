#include "renderer.hpp"
using namespace rayster;

#include <iostream>
#include <numeric>

void renderer::render_triangle(triangle t, shader& s) {
    auto iaw = 1 / t.a.w;
    auto ibw = 1 / t.b.w;
    auto icw = 1 / t.c.w;

    t.a *= iaw;
    t.b *= ibw;
    t.c *= icw;

    vector2 min = {
        static_cast<double>(fb_->width() - 1), 
        static_cast<double>(fb_->height() - 1)
    };
    vector2 max = {0, 0};
    for (int i = 0; i < 3; ++i) {
        t[i].x = (t[i].x + 1) / 2 * (fb_->width() - 1);
        t[i].y = (1 - t[i].y) / 2 * (fb_->height() - 1);

        for (int j = 0; j < 2; ++j) {
            min[j] = std::min(min[j], t[i][j]);
            max[j] = std::max(max[j], t[i][j]);
        }
    }

    for (auto x = min.x; x <= max.x; ++x) {
        for (auto y = min.y; y <= max.y; ++y) {
            auto bar = t.barycentric({x, y});
            if (bar.x < 0 || bar.y < 0 || bar.z < 0)
                continue;

            (*fb_)(x, y).color = s.frag(bar);

        }
    }
}

void renderer::render(int n, shader& s) {    
    for (int i = 0; i < n; i += 3) {
        triangle t;
        t.a = s.vert(i + 0);
        t.b = s.vert(i + 1);
        t.c = s.vert(i + 2);

        render_triangle(t, s);        
    }
}