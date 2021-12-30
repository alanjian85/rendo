#include <fstream>

#include "framebuffer.hpp"
#include "triangle.hpp"
using namespace rayster;

int main() {
    framebuffer fb(800, 600);

    triangle tri;
    tri.a = {  0,   0, 0};
    tri.b = {400, 600, 0};
    tri.c = {800,   0, 0};

    auto bbox = tri.bounding_box();
    for (auto x = bbox.min.x; x <= bbox.max.x; ++x) {
        for (auto y = bbox.min.y; y <= bbox.max.y; ++y) {
            auto bc = tri.barycentric({x, y});
            if (bc.x < 0 || bc.y < 0 || bc.z < 0) continue;
            fb(x, y) = {1, 0, 0};
        }
    }

    std::ofstream file("image.ppm");
    file << fb;
}