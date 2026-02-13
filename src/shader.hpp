#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <optional>

#include "logger.hpp"

class Shader {
public:
    ~Shader();

    void load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

    unsigned int getShaderProgram();

    void use();

private:
    std::optional<unsigned int> createShader(unsigned int shaderType, const std::string& path);

    std::string fetch(const std::string& path);

    GLuint shaderProgram;
};