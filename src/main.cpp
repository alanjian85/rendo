#include <iostream>
#include <optional>

#include "camera.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "model.hpp"
#include "light.hpp"
#include "utility.hpp"

#include "bloom_shader.hpp"
#include "blur_shader.hpp"
#include "bright_shader.hpp"
#include "depth_shader.hpp"
#include "diffuse_shader.hpp"
#include "emission_shader.hpp"
#include "normal_shader.hpp"
#include "position_shader.hpp"
#include "specular_shader.hpp"
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

        auto mvp = cam.proj(fb.aspect()) * cam.view();

        position_shader ps(mvp, diablo);
        normal_shader ns(mvp, diablo);
        diffuse_shader ds(mvp, diablo);
        specular_shader ss(mvp, diablo);
        emission_shader es(mvp, diablo);

        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), ps); auto g_position = fb.color_buffer();
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), ns); auto g_normal = fb.color_buffer();
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), ds); auto g_diffuse = fb.color_buffer();
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), ss); auto g_specular = fb.color_buffer();
        fb.clear({0, 0, 0, 1}); r.render(diablo.num_vertices(), es); auto g_emission = fb.color_buffer();

        fb.write("image.pam");
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}