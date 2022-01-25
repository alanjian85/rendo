#include <iostream>
#include <optional>

#include "camera.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "model.hpp"
#include "utility.hpp"
using namespace box;

class object_shader : public basic_shader {
public:
    object_shader(const camera& cam, double aspect) 
        : camera_(cam),
          aspect_(aspect)
    {
        cubemap_.load("assets/textures/skybox/");
        sampler_cube_.bind_cubemap(cubemap_);
    }

    virtual vector4 vert(int n) override {
        auto pos = model_->get_vertex(n);
        v_pos[n % 3] = pos;
        v_normal[n % 3] = model_->get_normal(n);
        sampler_.bind_texture(model_->get_mat(n)->diffuse_map);
        return camera_.proj(aspect_) * camera_.view() * vector4(pos, 1);
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto pos = frag_lerp(v_pos, bar);
        auto normal = frag_lerp(v_normal, bar);
        auto cam_dir = (camera_.pos - pos).normalize();
        auto color = sampler_cube_(reflect(cam_dir, normal));
        if (color.a < 0.1)
            return std::nullopt;
        return color;
    }
    
    void bind_model(const model& m) {
        model_ = &m;
    }
private:
    double aspect_;
    const camera& camera_;
    const model* model_;

    vector3 v_pos[3];
    vector3 v_normal[3];

    sampler2 sampler_;

    cubemap cubemap_;
    sampler_cube sampler_cube_;
};

int main() {
    try {
        renderer r;
        r.clear({0.90, 0.88, 0.84, 1.0});
        r.set_face_culling(cull_type::back);

        camera cam;
        cam.pos.y = 6;
        cam.pos.z = 6;
        cam.pitch = -45;

        model cube("assets/models/cube.obj");
        object_shader s(cam, r.aspect());
        s.bind_model(cube);
        r.render(cube.num_vertices(), s);

        r.write("image.pam");
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}