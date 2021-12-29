#include <cmath>
#include <fstream>

#include "framebuffer.hpp"
#include "triangle.hpp"
#include "viewport.hpp"
using namespace rayster;

int main() {
    framebuffer fb(800, 600);

    triangle tri;
    tri.a = {   0,   0, 0};
    tri.b = {0.25, 0.5, 0};
    tri.c = { 0.5,   0, 0};

    viewport view;
    view.min = {0, 0};
    view.max = {800, 600};

    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 2; ++j) {
            tri[i][j] = tri[i][j] * (view.max[j] - view.min[j]) + view.min[j];
        }
    }

    auto bbox = tri.bbox();
    auto view_bbox = view.bbox();
    for (auto x = std::floor(bbox.min.x); x <= bbox.max.x; ++x) {
        for (auto y = std::floor(bbox.min.y); y <= bbox.max.y; ++y) {
            if (view_bbox.inbound({x, y})) {
                fb(x, y) = {1, 0, 0};
            }
        }
    }

    std::ofstream file("image.ppm");
    file << fb;
}
