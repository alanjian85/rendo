#include <fstream>
#include <iostream>

#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "utility.hpp"
using namespace rayster;

class basic_shader : public shader {
public:
    basic_shader(const framebuffer& fb)
        : persp_(rad(45), fb.aspect(), 0.1, 100.0),
          lookat_({0, 0, 3}, {0, 0, 0}, {0, 1, 0}),
          rotate_(rad(45), {1, 1, 1})
    {
        skybox_right_.load("res/textures/right.ppm");
        skybox_left_.load("res/textures/left.ppm");
        skybox_top_.load("res/textures/top.ppm");
        skybox_bottom_.load("res/textures/bottom.ppm");
        skybox_back_.load("res/textures/back.ppm");
        skybox_front_.load("res/textures/front.ppm");
        sampler_.bind_right(skybox_right_);
        sampler_.bind_left(skybox_left_);
        sampler_.bind_top(skybox_top_);
        sampler_.bind_bottom(skybox_bottom_);
        sampler_.bind_back(skybox_back_);
        sampler_.bind_front(skybox_front_);
    }
    
    virtual vertex vert(const vertex& vert) override {
        return {persp_ * lookat_ * rotate_ * vert.pos, {vert.pos.x, vert.pos.y, vert.pos.z}};
    }

    virtual color_rgba frag(const vertex_data& data) override {
        return sampler_(data.pos);
    }
private:
    texture skybox_right_;
    texture skybox_left_;
    texture skybox_top_;
    texture skybox_bottom_;
    texture skybox_back_;
    texture skybox_front_;
    sampler_cube sampler_;

    persp persp_;
    lookat lookat_;
    rotate rotate_;
};

int main() {
    renderer render;
    render.clear({0.627, 0.906, 0.898, 1.0});

    cube c(1);

    basic_shader s(render.fb());
    render.draw_cube(c, s);

    render.fb().write("image.ppm");
}