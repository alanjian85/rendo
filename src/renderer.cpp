#include "renderer.hpp"
using namespace rayster;

void renderer::draw_triangle(triangle tri, shader& s) noexcept {
    tri.a = s.vert(tri.a);
    tri.b = s.vert(tri.b);
    tri.c = s.vert(tri.c);

    auto ndc = view_.transform();
    tri.a.pos = ndc * tri.a.pos;
    tri.b.pos = ndc * tri.b.pos;
    tri.c.pos = ndc * tri.c.pos;

    auto bbox = tri.bounding_box();
    for (auto x = bbox.min.x; x <= bbox.max.x; ++x) {
        for (auto y = bbox.min.y; y <= bbox.max.y; ++y) {
            if (view_.bounding_box().inbound({x, y})) {
                auto bc = tri.barycentric({x, y});
                if (bc.x < 0 || bc.y < 0 || bc.z < 0) continue;
            
                auto data = bc.x * tri.a.data + bc.y * tri.b.data + bc.z * tri.c.data;
                fb_(x, y).color = s.frag(data);
            }
        }
    }
}