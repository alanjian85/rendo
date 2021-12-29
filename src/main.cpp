#include <fstream>

#include "clip_triangle.hpp"
#include "framebuffer.hpp"
using namespace rayster;

int main() {
    framebuffer fb({800, 600});

    clip_triangle tri;
    tri.a = {  0,   0};
    tri.b = {200, 300};
    tri.c = {400,   0};

    auto bbox = tri.bbox();
    for (int x = bbox.min.x; x <= bbox.max.x; ++x) {
        for (int y = bbox.min.y; y <= bbox.max.y; ++y) {
            if (x < 0 || x >= fb.width() || y < 0 || y >= fb.height()) continue;
            fb[{x, y}] = {1, 0, 0};
        }
    }

    std::ofstream file("image.ppm");
    file << fb;
}