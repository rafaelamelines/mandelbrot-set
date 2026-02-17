#pragma once

#include <stb_image.h>
#include <GLFW/glfw3.h>

#include <string>

extern const std::string BASE_PATH;

namespace cursor {
    inline GLFWcursor* cursor;
    inline GLFWimage defaultCursor;
    inline GLFWimage moveCursor;

    void init();
}