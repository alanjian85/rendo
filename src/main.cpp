#include <iostream>
#include <optional>

#include "camera.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "model.hpp"
#include "light.hpp"
#include "utility.hpp"

#include "albedo_shader.hpp"
#include "bloom_shader.hpp"
#include "blur_shader.hpp"
#include "bright_shader.hpp"
#include "deferred_shader.hpp"
#include "emission_shader.hpp"
#include "normal_shader.hpp"
#include "position_shader.hpp"
#include "shadow_shader.hpp"
#include "specular_shader.hpp"
#include "ssao_blur_shader.hpp"
#include "ssao_shader.hpp"
using namespace box;

int main() {
    try {
        framebuffer fb(1024, 1024);
        renderer r(fb);

        model diablo;
        model quad;
        diablo.load("assets/models/diablo3_pose.obj");
        quad.load("assets/models/quad.obj");

        camera cam;
        cam.pos.x = 0;
        cam.pos.y = 0.65;
        cam.pos.z = 2;
        cam.yaw = -90;
        cam.pitch = -15;

        auto proj = cam.proj(fb.aspect());
        auto view = cam.view();

        directional_light light;
        light.dir = vector3(0, 0, -2);
        light.ambient = color_rgb(0.3);
        light.diffuse = color_rgb(1.0);
        light.specular = color_rgb(0.5);

        auto light_proj = make_ortho(-1, 1, -1, 1, 1, 7.5);
        auto light_view = make_lookat(-light.dir, vector3(0, 0, 0), vector3(0, 1, 0));

        position_shader ps(proj, view, diablo);
        normal_shader ns(proj, view, diablo);
        albedo_shader as(proj, view, diablo);
        specular_shader ss(proj, view, diablo);
        emission_shader es(proj, view, diablo);

        shadow_shader sss(light_proj, light_view, diablo);
        r.set_face_culling(cull_type::front);
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), sss); auto shadowmap = fb.zbuffer();

        r.set_face_culling(cull_type::back);
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), ps); auto g_position = fb.color_buffer();
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), ns); auto g_normal = fb.color_buffer();
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), as); auto g_albedo = fb.color_buffer();
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), ss); auto g_specular = fb.color_buffer();
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), es); auto g_emission = fb.color_buffer();

        r.set_face_culling(cull_type::none);

        ssao_shader ssaos(proj, quad, g_position, g_normal, fb.width(), fb.height());
        fb.clear({0, 0, 0, 1}); r.render(quad.num_vertices(), ssaos); auto g_ssao = fb.color_buffer();

        ssao_blur_shader ssaobs(quad, g_ssao);
        fb.clear({0, 0, 0, 1}); r.render(quad.num_vertices(), ssaobs); auto g_ambient = fb.color_buffer();

        deferred_shader ds(view, quad, light, light_proj, light_view, shadowmap);
        ds.set_position_buffer(g_position);
        ds.set_normal_buffer(g_normal);
        ds.set_ambient_buffer(g_ambient);
        ds.set_albedo_buffer(g_albedo);
        ds.set_specular_buffer(g_specular);
        ds.set_emission_buffer(g_emission);
        fb.clear({0, 0, 0, 1});
        r.render(quad.num_vertices(), ds);

        auto scene = fb.color_buffer();
        bright_shader brights(quad, scene);
        r.render(quad.num_vertices(), brights);

        bool horizontal = true;
        for (int i = 0; i < 10; ++i) {
            auto bright = fb.color_buffer();
            blur_shader blurs(quad, bright, horizontal);
            r.render(quad.num_vertices(), blurs);
            horizontal = !horizontal;
        }

        auto blur = fb.color_buffer();
        bloom_shader blooms(quad, scene, blur);
        r.render(quad.num_vertices(), blooms);

        fb.write("image.pam");

    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}