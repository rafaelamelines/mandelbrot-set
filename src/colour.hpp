#pragma once

#include <glad/glad.h>

#include "shader.hpp"

inline int colour = 1;

struct Colour {
    float r, g, b;
};

void populateColours(const Shader& shader);