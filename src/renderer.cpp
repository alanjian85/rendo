#include "renderer.hpp"
using namespace rayster;

void renderer::draw_triangle(const triangle& tri) noexcept {
    auto bbox = tri.bounding_box();
    for (auto x = bbox.min.x; x <= bbox.max.x; ++x) {
        for (auto y = bbox.min.y; y <= bbox.max.y; ++y) {
            auto bc = tri.barycentric({x, y});
            if (bc.x < 0 || bc.y < 0 || bc.z < 0) continue;
            fb_(x, y) = {1, 0, 0};
        }
    }
}