#include <fstream>

#include "framebuffer.hpp"
#include "triangle.hpp"
using namespace rayster;

int main() {
    triangle tri;
    tri.a = {  0, 0, 0};
    tri.b = {0.5, 1, 0};
    tri.c = {  1, 0, 0};

    auto bbox = tri.bbox();
    for (auto x = static_cast<int>(bbox.min.x); x <= bbox.max.x; ++x) {
        for (auto y = static_cast<int>(bbox.min.y); y <= bbox.max.y; ++y) {

        }
    }
}
