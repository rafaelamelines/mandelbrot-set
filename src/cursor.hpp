#pragma once

#include <stb_image.h>
#include <GLFW/glfw3.h>

#include <string>

extern const std::string BASE_PATH;

namespace cursor {
    inline GLFWcursor* cursor;
    inline GLFWimage defaultCursor;
    inline GLFWimage moveCursor;

    inline void init() {
        int width, height;
        unsigned char* data = stbi_load((BASE_PATH + "resources/cursor_default.png").c_str(), &width, &height, nullptr, STBI_rgb_alpha);
        defaultCursor = { width, height, data };

        data = stbi_load((BASE_PATH + "resources/cursor_move.png").c_str(), &width, &height, nullptr, STBI_rgb_alpha);
        moveCursor = { width, height, data };
    }
}