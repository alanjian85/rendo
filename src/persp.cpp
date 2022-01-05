#include "persp.hpp"
using namespace rayster;

#include <cmath>

persp::persp(double fov, double aspect, double near, double far) noexcept {
    auto t = std::tan(fov / 2);
    
    (*this)(0, 0) = 1 / (aspect * t);
    (*this)(1, 1) = 1 / t;
    (*this)(2, 2) = far / (far - near);
    (*this)(2, 3) = -(far * near) / (far - near);
    (*this)(3, 2) = 1;
}