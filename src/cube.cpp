#include "cube.hpp"
using namespace rayster;

cube::cube(double size) noexcept {
    auto t = size / 2;
    triangles_[0] =  {{-t,  t,  t, 0, 1}, {-t, -t,  t, 0, 0}, { t,  t,  t, 1, 1}};
    triangles_[1] =  {{-t, -t,  t, 0, 0}, { t,  t,  t, 1, 1}, { t, -t,  t, 1, 0}};
    
    triangles_[2] =  {{-t,  t, -t, 0, 1}, {-t, -t, -t, 0, 0}, { t,  t, -t, 1, 1}};
    triangles_[3] =  {{-t, -t, -t, 0, 0}, { t,  t, -t, 1, 1}, { t, -t, -t, 1, 0}};
    
    triangles_[4] =  {{-t,  t, -t, 0, 1}, {-t, -t, -t, 0, 0}, {-t,  t,  t, 1, 1}};
    triangles_[5] =  {{-t, -t, -t, 0, 0}, {-t,  t,  t, 1, 1}, {-t, -t,  t, 1, 0}};
         
    triangles_[6] =  {{ t,  t, -t, 0, 1}, { t, -t, -t, 0, 0}, { t,  t,  t, 1, 1}};
    triangles_[7] =  {{ t, -t, -t, 0, 0}, { t,  t,  t, 1, 1}, { t, -t,  t, 1, 0}};
          
    triangles_[8] =  {{-t,  t, -t, 0, 1}, {-t,  t,  t, 0, 0}, { t,  t, -t, 1, 1}};
    triangles_[9] =  {{-t,  t,  t, 0, 0}, { t,  t, -t, 1, 1}, { t,  t,  t, 1, 0}};
          
    triangles_[10] = {{-t, -t, -t, 0, 1}, {-t, -t,  t, 0, 0}, { t, -t, -t, 1, 1}};
    triangles_[11] = {{-t, -t,  t, 0, 0}, { t, -t, -t, 1, 1}, { t, -t,  t, 1, 0}};
} 