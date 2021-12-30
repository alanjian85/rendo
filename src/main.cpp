#include "renderer.hpp"
using namespace rayster;

int main() {
    renderer render;

    triangle tri;
    tri.a = {  0,   0, 0};
    tri.b = {200, 300, 0};
    tri.c = {400,   0, 0};
    render.draw_triangle(tri);

    render.write("image.ppm");
}