#include "colour.hpp"

void populateColours(const Shader& shader) {
    // black to colour
    for (size_t i = 0; i < 64; i++) {
        Colour c = {
            (float)((colour & 1) * i) / 64.0f,         // clever bitwise operation thing that returns i / 64 if the colour has red, 0 if not.
            (float)(((colour & 2) >> 1) * i) / 64.0f,  // clever bitwise operation thing that returns i / 64 if the colour has green, 0 if not.
            (float)(((colour & 4) >> 2) * i) / 64.0f   // clever bitwise operation thing that returns i / 64 if the colour has blue, 0 if not.
        };
        GLint colourUniform = glGetUniformLocation(shader.getShaderProgram(), ("COLOURS[" + std::to_string(i) + "]").c_str());
        glUniform4f(colourUniform, c.r, c.g, c.b, 1.0f);
    }

    // colour to white
    for (size_t i = 0; i < 64; i++) {
        Colour c = {
            1.0f - (float)(!(colour & 1) * (64 - i)) / 64.0f,        // even more clever bitwise operation thing that returns 1 if the colour has red, i / 64 if not
            1.0f - (float)(!((colour & 2) >> 1) * (64 - i)) / 64.0f, // even more clever bitwise operation thing that returns 1 if the colour has green, i / 64 if not
            1.0f - (float)(!((colour & 4) >> 2) * (64 - i)) / 64.0f  // even more clever bitwise operation thing that returns 1 if the colour has blue, i / 64 if not
        };
        GLint colourUniform = glGetUniformLocation(shader.getShaderProgram(), ("COLOURS[" + std::to_string(i + 64) + "]").c_str());
        glUniform4f(colourUniform, c.r, c.g, c.b, 1.0f);
    }
}