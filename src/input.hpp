#include <GLFW/glfw3.h>

extern const size_t WINDOW_SIZE;

extern float scaleFactor;
extern double originX, originY;

namespace input_handler {
    inline bool dragging = false;
    inline double previousX, previousY;
    inline double cursorX, cursorY;
    inline const double ZOOM_FACTOR = 1.02;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void mouse_pos_callback(GLFWwindow* window, double x, double y) {
        if (dragging) {
            originX += x - previousX;
            originY += previousY - y;
        }
        previousX = x;
        previousY = y;
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS)
                dragging = true;
            else if (action == GLFW_RELEASE)
                dragging = false;
        }
    }

    void scroll_callback(GLFWwindow* window, [[maybe_unused]]double dx, double dy) {
        glfwGetCursorPos(window, &cursorX, &cursorY);
        cursorY = (double)WINDOW_SIZE - cursorY;

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

    void processInput(GLFWwindow *window) {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
}