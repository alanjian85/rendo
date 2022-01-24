#include <iostream>
#include <optional>

#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "model.hpp"
#include "utility.hpp"
using namespace box;

class shader : public basic_shader {
public:
    shader(double aspect)        
        : persp_(make_persp(rad(45), aspect, 0.1, 100)),
          lookat_(make_lookat({0, 0, 6}, {0, 0, 0}, {0, 1, 0})),
          rotate_(make_rotate(rad(45), {1, 1, 1}))
    {
        sampler_.set_wrap(wrapping::clamp_to_edge);
    }

    virtual vector4 vert(int n) override {
        v_tex_coords[n % 3] = model_->get_tex_coord(n);
        sampler_.bind_texture(model_->get_mat(n)->diffuse_map);
        return persp_ * lookat_ * rotate_ * model_->get_vertex(n);
    }

    virtual color_rgba frag(vector3 bar) override {
        auto tex_coord = frag_lerp(v_tex_coords, bar);
        auto color = sampler_(tex_coord);
        return color;
    }
    
    void bind_model(const model& m) {
        model_ = &m;
    }
private:
    const model* model_;

    matrix4 persp_;
    matrix4 lookat_;
    matrix4 rotate_;

    vector3 v_tex_coords[3];

    sampler2 sampler_;
};

int main() {
    try {
        renderer r;
        r.clear({0.90, 0.88, 0.84, 1.0});

        shader s(r.aspect());

        model cube("assets/models/cube.obj");
        s.bind_model(cube);
        r.render(cube.num_vertices(), s);

        r.write("image.pam");
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}