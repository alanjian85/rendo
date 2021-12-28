#ifndef SENTINEL_RENDERER_HPP
#define SENTINEL_RENDERER_HPP

#include <fstream>
#include <string>

#include "framebuffer.hpp"

namespace sentinel {
    class renderer {
    public:
        renderer(int width, int height) 
            : fb_(width, height)
        {
            fb_.clear({1, 0, 0});
        }

        void write(const std::string& path) {
            std::ofstream file(path);
            file << fb_;
        }
    private:
        framebuffer fb_;
    };
}

#endif
