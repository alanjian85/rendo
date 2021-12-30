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
            auto bc = tri.barycentric({x, y});
            if (bc.x < 0 || bc.y < 0 || bc.z < 0) continue;
            fb(x, y) = {1, 0, 0};
        }
    }

    std::ofstream file("image.ppm");
    file << fb;
}