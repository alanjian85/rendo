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
#include "depth_shader.hpp"
#include "emission_shader.hpp"
#include "normal_shader.hpp"
#include "position_shader.hpp"
#include "specular_shader.hpp"
#include "ssao_shader.hpp"
using namespace box;

int main() {
    try {
        camera cam;
        cam.pos.x = 0;
        cam.pos.y = 0.65;
        cam.pos.z = 2;
        cam.yaw = -90;
        cam.pitch = -15;

        model diablo;
        model quad;
        diablo.load("assets/models/diablo3_pose.obj");
        quad.load("assets/models/quad.obj");

        directional_light light;
        light.dir = vector3(0, 0.65, 2);
        light.ambient = color_rgb(0.1);
        light.diffuse = color_rgb(1.0);
        light.specular = color_rgb(0.5);

        framebuffer fb(1024, 1024);
        renderer r(fb);

        auto proj = cam.proj(fb.aspect());
        auto view = cam.view();
        auto mvp = proj * view;

        position_shader ps(mvp, diablo);
        normal_shader ns(mvp, diablo);
        albedo_shader as(mvp, diablo);
        specular_shader ss(mvp, diablo);
        emission_shader es(mvp, diablo);

        auto light_mvp = light.proj(0) * light.view();
        depth_shader shadow_ds(light_mvp, diablo);
        r.set_face_culling(cull_type::front);
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), shadow_ds); auto shadowmap = fb.zbuffer();

        r.set_face_culling(cull_type::back);
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), ps); auto g_position = fb.color_buffer();
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), ns); auto g_normal = fb.color_buffer();
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), as); auto g_albedo = fb.color_buffer();
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), ss); auto g_specular = fb.color_buffer();
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), es); auto g_emission = fb.color_buffer();
        
        r.set_face_culling(cull_type::none);
        ssao_shader ssaos(proj, quad, g_position, g_normal, fb.width(), fb.height());
        fb.clear({0, 0, 0, 1}); r.render(quad.num_vertices(), ssaos); auto g_ambient = fb.color_buffer();

        deferred_shader ds(quad, light, cam.pos, light_mvp, shadowmap);
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