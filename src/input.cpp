#include "input.hpp"

void input_handler::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    windowWidth = width;
    windowHeight = height;
}

void input_handler::mouse_pos_callback(GLFWwindow* window, double x, double y) {
    if (dragging) {
        originX += x - previousX;
        originY += previousY - y;
    }
    previousX = x;
    previousY = y;
}

void input_handler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            glfwDestroyCursor(cursor::cursor);
            cursor::cursor = glfwCreateCursor(&cursor::moveCursor, 12, 12);
            glfwSetCursor(window, cursor::cursor);
            dragging = true;
        } else if (action == GLFW_RELEASE) {
            glfwDestroyCursor(cursor::cursor);
            cursor::cursor = glfwCreateCursor(&cursor::defaultCursor, 0, 0);
            glfwSetCursor(window, cursor::cursor);
            dragging = false;
        }
    }
}

void input_handler::scroll_callback(GLFWwindow* window, [[maybe_unused]]double dx, double dy) {
    glfwGetCursorPos(window, &cursorX, &cursorY);
    cursorY = (double)windowHeight - cursorY;

    if (dy > 0) {
        originX = (originX - cursorX) * ZOOM_FACTOR + cursorX;
        originY = (originY - cursorY) * ZOOM_FACTOR + cursorY;
        scaleFactor *= (float)ZOOM_FACTOR;
    } else {
        originX = (originX - cursorX) / ZOOM_FACTOR + cursorX;
        originY = (originY - cursorY) / ZOOM_FACTOR + cursorY;
        scaleFactor /= (float)ZOOM_FACTOR;
    }
}

void input_handler::processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
