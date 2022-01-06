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

    tri.a.pos.w = 1 / tri.a.pos.w;
    tri.b.pos.w = 1 / tri.b.pos.w;
    tri.c.pos.w = 1 / tri.c.pos.w;

    tri.a.pos.x *= tri.a.pos.w;
    tri.b.pos.x *= tri.b.pos.w;
    tri.c.pos.x *= tri.c.pos.w;

    tri.a.pos.y *= tri.a.pos.w;
    tri.b.pos.y *= tri.b.pos.w;
    tri.c.pos.y *= tri.c.pos.w;

    tri.a.pos.z *= tri.a.pos.w;
    tri.b.pos.z *= tri.b.pos.w;
    tri.c.pos.z *= tri.c.pos.w;

    tri.a.data *= tri.a.pos.w;
    tri.b.data *= tri.b.pos.w;
    tri.c.data *= tri.c.pos.w;

    auto bbox = tri.bounding_box();
    bbox = intersection(bbox, view_.bounding_box());
    for (auto x = bbox.min.x; x <= bbox.max.x; ++x) {
        for (auto y = bbox.min.y; y <= bbox.max.y; ++y) {
            auto bc = tri.barycentric({x, y});
            if (bc.x < 0 || bc.y < 0 || bc.z < 0) continue;
            
            auto w = 1 / (bc.x * tri.a.pos.w + bc.y * tri.b.pos.w + bc.z * tri.c.pos.w);
            auto z = bc.x * tri.a.pos.z + bc.y * tri.b.pos.z + bc.z * tri.c.pos.z;
            auto data = (bc.x * tri.a.data + bc.y * tri.b.data + bc.z * tri.c.data) * w;
            if (fb_.depth_test(x, y, z)) {
                fb_(x, y).color = s.frag(data);
                fb_(x, y).depth = z;
            }
        }
    }
}