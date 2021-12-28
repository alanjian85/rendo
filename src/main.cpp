#include <fstream>

#include "renderer.hpp"
using namespace sentinel;

int main() {
    renderer r(800, 600);

    r.write("image.ppm");
}
