#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <filesystem>

#include "logger.hpp"
#include "shader.hpp"
#include "input.hpp"

const size_t WINDOW_SIZE = 800;

float scaleFactor = 100.0f;
double originX = (double)WINDOW_SIZE / 2.0;
double originY = (double)WINDOW_SIZE / 2.0;

struct Colour {
    float r, g, b;
};

Colour colours[64];

void populateColours() {
    for (size_t i = 0; i < 32; i++) {
        colours[i] =  { 0.0f, 0.0f, (float)i / 64.0f };
    }

    for (size_t i = 0; i < 32; i++) {
        colours[i + 32] = { (float)i / 64.0f, (float)i / 64.0f, 1.0f };
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE, WINDOW_SIZE, "Mandelbrot set", nullptr, nullptr);
    if (!window) {
        MANDEL_ERROR("Failed to create GLFW window");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, input_handler::framebuffer_size_callback);
    glfwSetScrollCallback(window, input_handler::scroll_callback);
    glfwSetMouseButtonCallback(window, input_handler::mouse_button_callback);
    glfwSetCursorPosCallback(window, input_handler::mouse_pos_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        MANDEL_ERROR("Failed to initialize GLAD");
        return 1;
    }

    Shader mandelShader;
    std::string basePath = std::filesystem::current_path().parent_path().string() + '/';
    mandelShader.load(basePath + "shader/mandel.vert.glsl", basePath + "shader/mandel.frag.glsl");
    mandelShader.use();

    float vertices[] = {
         1.0f,  1.0f, 0.0f,  // top right
         1.0f, -1.0f, 0.0f,  // bottom right
        -1.0f, -1.0f, 0.0f,  // bottom left
        -1.0f,  1.0f, 0.0f   // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int vertexBufferObject, vertexArrayObject, elementBufferObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glGenBuffers(1, &elementBufferObject);

    glBindVertexArray(vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    GLint windowDimensionsUniform = glGetUniformLocation(mandelShader.getShaderProgram(), "WINDOW_DIMENSIONS");
    glUniform2f(windowDimensionsUniform, (float)WINDOW_SIZE, (float)WINDOW_SIZE);

    GLint maxIterationsUniform = glGetUniformLocation(mandelShader.getShaderProgram(), "MAX_ITERATIONS");
    glUniform1i(maxIterationsUniform, 128);

    GLint thresholdUniform = glGetUniformLocation(mandelShader.getShaderProgram(), "THRESHOLD");
    glUniform1f(thresholdUniform, 16.0f);

    populateColours();

    for (size_t i = 0; i < 64; i++) {
        Colour colour = colours[i];
        GLint colourUniform = glGetUniformLocation(mandelShader.getShaderProgram(), ("COLOURS[" + std::to_string(i) + "]").c_str());
        glUniform4f(colourUniform, colour.r, colour.g, colour.b, 1.0f);
    }

    input_handler::framebuffer_size_callback(window, WINDOW_SIZE, WINDOW_SIZE);

    while (!glfwWindowShouldClose(window)) {
        input_handler::processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        mandelShader.use();

        GLint scaleFactorUniform = glGetUniformLocation(mandelShader.getShaderProgram(), "scaleFactor");
        glUniform1f(scaleFactorUniform, scaleFactor);

        GLint originUniform = glGetUniformLocation(mandelShader.getShaderProgram(), "originWindowCoords");
        glUniform2f(originUniform, (float)originX, (float)originY);

        glBindVertexArray(vertexArrayObject);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &elementBufferObject);
    glDeleteProgram(mandelShader.getShaderProgram());

    glfwTerminate();
}