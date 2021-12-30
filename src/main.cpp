#include "renderer.hpp"
using namespace rayster;

int main() {
    renderer render;

    triangle tri;
    tri.a = {   0,    0, 0};
    tri.b = { 800, 1200, 0};
    tri.c = {1600,    0, 0};
    render.draw_triangle(tri);

    render.write("image.ppm");
}