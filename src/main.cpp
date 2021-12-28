#include <fstream>

#include "framebuffer.hpp"
using namespace sentinel;

int main() {
    framebuffer fb(800, 600, {1, 0, 0});

    std::ofstream file("image.ppm");
    file << fb;
}
