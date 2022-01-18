#include "renderer.hpp"
using namespace rayster;

#include <numeric>

void renderer::render(triangle t, shader& s) {    
    vector2 min = {fb_->width() - 1, fb_->height() - 1};
    vector2 max = {0, 0};
    for (int i = 0; i < 3; ++i) {
        t[i].x = (t[i].x + 1) / 2 * (fb_->width() - 1);
        t[i].y = (t[i].y + 1) / 2 * (fb_->height() - 1);
        for (int j = 0; j < 2; ++j) {
            min[j] = std::min(min[j], t[i][j]);
            max[j] = std::max(max[j], t[i][j]);
        }
    }
    
}

void renderer::render(const model& m, shader& s) {
    for (int i = 0; i < m.num_faces(); ++i) {
        
    }
}