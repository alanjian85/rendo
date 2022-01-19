#include "renderer.hpp"
using namespace rayster;

#include <numeric>

void renderer::render(int n, shader& s) {    
    for (int i = 0; i < n; i += 3) {
        auto a = s.vert(i + 0);
        
    }
}