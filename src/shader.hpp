#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <optional>

#include "logger.hpp"

class Shader {
public:
    ~Shader() {
        glDeleteProgram(shaderProgram);
    }

    void load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
        auto vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderPath);
        auto fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

        if (!vertexShader.has_value() || !fragmentShader.has_value()) {
            MANDEL_ERROR("one of shader has no value");
            return;
        }

        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader.value());
        glAttachShader(shaderProgram, fragmentShader.value());
        glLinkProgram(shaderProgram);

        int programSuccess;
        char programInfoLog[512];

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programSuccess);

        if(!programSuccess) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, programInfoLog);
            MANDEL_ERROR("Error: Shader could not be loaded: ", programInfoLog);
        }

        glDeleteShader(vertexShader.value());
        glDeleteShader(fragmentShader.value());
    }

    unsigned int getShaderProgram() {
        return shaderProgram;
    }

    void use() {
        glUseProgram(shaderProgram);
    }

private:
    std::optional<unsigned int> createShader(unsigned int shaderType, std::string path) {
        unsigned int shader = glCreateShader(shaderType);

        std::string shaderSource = fetch(path);
        const char* shaderSourceCString = shaderSource.c_str();
        glShaderSource(shader, 1, &shaderSourceCString, NULL);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
            MANDEL_ERROR("Shader '", path, "' could not be compiled");
            MANDEL_ERROR(infoLog);

            return {};
        }

        return shader;
    }

    std::string fetch(const std::string& path) {
        std::ifstream file(path.data());
        std::stringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    }

    GLuint shaderProgram;
};