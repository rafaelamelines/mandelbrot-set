#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "cursor.hpp"

extern const size_t WINDOW_SIZE;

extern float scaleFactor;
extern double originX, originY;

namespace input_handler {
    inline bool dragging = false;
    inline double previousX, previousY;
    inline double cursorX, cursorY;
    inline const double ZOOM_FACTOR = 1.02;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_pos_callback(GLFWwindow* window, double x, double y);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void scroll_callback(GLFWwindow* window, [[maybe_unused]]double dx, double dy);

    void processInput(GLFWwindow *window);
}