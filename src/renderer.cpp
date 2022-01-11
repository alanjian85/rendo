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

    auto iaw = 1 / tri.a.pos.w;
    auto ibw = 1 / tri.b.pos.w;
    auto icw = 1 / tri.c.pos.w;

    tri.a.pos *= iaw;
    tri.b.pos *= ibw;
    tri.c.pos *= icw;

    tri.a.data *= iaw;
    tri.b.data *= ibw;
    tri.c.data *= icw;

    auto bbox = tri.bounding_box();
    bbox = intersection(bbox, view_.bounding_box());
    for (auto x = bbox.min.x; x <= bbox.max.x; ++x) {
        for (auto y = bbox.min.y; y <= bbox.max.y; ++y) {
            auto bc = tri.barycentric({x, y});
            if (bc.x < 0 || bc.y < 0 || bc.z < 0) continue;
            
            auto w = 1 / (bc.x * iaw + bc.y * ibw + bc.z * icw);
            auto z = bc.x * tri.a.pos.z + bc.y * tri.b.pos.z + bc.z * tri.c.pos.z;
            auto data = (bc.x * tri.a.data + bc.y * tri.b.data + bc.z * tri.c.data) * w;
            if (fb_->depth_test(x, y, z)) {
                (*fb_)(x, y).color = s.frag(data);
                (*fb_)(x, y).depth = z;
            }
        }
    }
}