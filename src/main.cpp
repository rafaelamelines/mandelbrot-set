#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <filesystem>

#include "logger.hpp"
#include "shader.hpp"
#include "input.hpp"
#include "cursor.hpp"
#include "colour.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

const std::string BASE_PATH = std::filesystem::current_path().parent_path().string() + '/';

size_t windowWidth = 1200, windowHeight = 800;

float scaleFactor = 200.0f;
double originX = (double)windowWidth / 2.0 + 200.0;
double originY = (double)windowHeight / 2.0;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwSetErrorCallback(logger::GLFWErrorCallback);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Mandelbrot set", nullptr, nullptr);
    if (!window) {
        MANDEL_ERROR("Failed to create GLFW window");
        glfwTerminate();
        return 1;
    }

    {
        int iconWidth, iconHeight;
        unsigned char* iconData = stbi_load((BASE_PATH + "resources/icon.png").c_str(), &iconWidth, &iconHeight, nullptr, STBI_rgb_alpha);

        GLFWimage icon(iconWidth, iconHeight, iconData);

        glfwSetWindowIcon(window, 1, &icon);
    }

    cursor::init();

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
    mandelShader.load(BASE_PATH + "shader/mandel.vert.glsl", BASE_PATH + "shader/mandel.frag.glsl");
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

    populateColours(mandelShader);

    glViewport(0, 0, windowWidth, windowHeight);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    {
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.IniFilename = NULL;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        input_handler::processInput(window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize({ 400, (float)windowHeight });
        ImGui::SetNextWindowPos({ 0, 0 });
        ImGui::Begin("##settings", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        ImGui::Text("Multibrot set with exponent");
        static int p = 2;
        if (ImGui::InputInt("##multibrot", &p, 1, 1))
            if (p < 1)
                p = 1;

        ImGui::SeparatorText("");

        ImGui::Text("Colour");

        if (ImGui::RadioButton("Red", &colour, 1))
            populateColours(mandelShader);
        if (ImGui::RadioButton("Green", &colour, 2))
            populateColours(mandelShader);
        if (ImGui::RadioButton("Blue", &colour, 4))
            populateColours(mandelShader);
        if (ImGui::RadioButton("Yellow", &colour, 3))
            populateColours(mandelShader);
        if (ImGui::RadioButton("Pink", &colour, 5))
            populateColours(mandelShader);
        if (ImGui::RadioButton("Cyan", &colour, 6))
            populateColours(mandelShader);
        if (ImGui::RadioButton("White", &colour, 7))
            populateColours(mandelShader);

        ImGui::SeparatorText("");

        ImGui::Text("Threshold");

        static float threshold = 16.0f;
        if (ImGui::InputFloat("##threshold", &threshold))
            if (threshold < 0.0f)
                threshold = 0.0f;

        GLint thresholdUniform = glGetUniformLocation(mandelShader.getShaderProgram(), "threshold");
        glUniform1f(thresholdUniform, threshold);

        ImGui::End();

        glClear(GL_COLOR_BUFFER_BIT);

        mandelShader.use();

        GLint pUniform = glGetUniformLocation(mandelShader.getShaderProgram(), "p");
        glUniform1i(pUniform, p);

        GLint windowDimensionsUniform = glGetUniformLocation(mandelShader.getShaderProgram(), "WINDOW_DIMENSIONS");
        glUniform2f(windowDimensionsUniform, (float)windowWidth, (float)windowHeight);

        GLint scaleFactorUniform = glGetUniformLocation(mandelShader.getShaderProgram(), "scaleFactor");
        glUniform1f(scaleFactorUniform, scaleFactor);

        GLint originUniform = glGetUniformLocation(mandelShader.getShaderProgram(), "originWindowCoords");
        glUniform2f(originUniform, (float)originX, (float)originY);

        glBindVertexArray(vertexArrayObject);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &elementBufferObject);
    glDeleteProgram(mandelShader.getShaderProgram());

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}