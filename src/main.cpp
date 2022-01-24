#include <iostream>
#include <optional>

#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "model.hpp"
#include "utility.hpp"
using namespace rayster;

class shader : public basic_shader {
public:
    shader(double aspect)        
        : persp_(make_persp(rad(45), aspect, 0.1, 100)),
          lookat_(make_lookat({-4, 2.15, 6}, {0, 2.15, 0}, {0, 1, 0}))
    {
        sampler_.set_wrap(wrapping::clamp_to_edge);
    }

    virtual vector4 vert(int n) override {
        v_normals[n % 3] = model_->get_normal(n);
        v_tex_coords[n % 3] = model_->get_tex_coord(n);
        sampler_.bind_texture(model_->get_mat(n)->diffuse_map);
        return persp_ * lookat_ * translate_ * model_->get_vertex(n);
    }

    virtual color_rgba frag(vector3 bar) override {
        auto normal = frag_lerp(v_normals, bar);
        auto tex_coord = frag_lerp(v_tex_coords, bar);
        auto color = sampler_(tex_coord);
        return color;
    }
    
    void bind_model(const model& m) {
        model_ = &m;
    }

    void set_pos(vector3 pos) {
        translate_= make_translate(pos);
    }
private:
    const model* model_;

    matrix4 persp_;
    matrix4 lookat_;
    matrix4 translate_;

    vector3 v_tex_coords[3];
    vector3 v_normals[3];

    sampler2 sampler_;
};

int main() {
    try {
        renderer r;
        r.clear({0.90, 0.88, 0.84, 1.0});

        shader s(r.aspect());

        model aqua("assets/models/aqua.obj");
        s.bind_model(aqua);
        s.set_pos({0, 0, 0});
        r.render(aqua.num_vertices(), s);

        model rushia("assets/models/rushia.obj");
        s.bind_model(rushia);
        s.set_pos({2, 0, 0});
        r.render(rushia.num_vertices(), s);

        model pekora("assets/models/pekora.obj");
        s.bind_model(pekora);
        s.set_pos({-2, 0, 0});
        r.render(pekora.num_vertices(), s);

        r.write("image.pam");
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}