#include <iostream>

#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "model.hpp"
#include "utility.hpp"
using namespace rayster;

class hello_shader : public shader {
public:
    hello_shader(double aspect, const model& m) 
        : model_(m),
          persp_(rad(45), aspect, 0.1, 100),
          lookat_({0, 1.5, 9}, {0, 1.5, 0}, {0, 1, 0})
    {

    }

    virtual vector4 vert(int n) override {
        v_normals[n % 3] = model_.get_normal(n);
        v_tex_coords[n % 3] = model_.get_tex_coord(n);
        sampler_.bind_texture(model_.get_mat(n)->diffuse_map);
        return persp_ * lookat_ * model_.get_vertex(n);
    }

    virtual color_rgba frag(vector3 bar) override {
        auto normal = frag_lerp(v_normals, bar);
        auto tex_coord = frag_lerp(v_tex_coords, bar);
        return sampler_(tex_coord);
    }
private:
    const model& model_;

    persp persp_;
    lookat lookat_;

    vector3 v_tex_coords[3];
    vector3 v_normals[3];

    sampler2 sampler_;
};

int main() {
    renderer r;
    r.clear({0.627, 0.906, 0.898, 1.0});

    model m;
    m.load("res/models/aqua.obj");

    hello_shader s(r.aspect(), m);
    r.render(m.num_vertices(), s);

    r.write("output/image.ppm");
}