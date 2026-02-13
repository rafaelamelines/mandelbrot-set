#version 330 core
out vec4 FragColor;

uniform vec4 COLOURS[128];
uniform int P;
uniform int MAX_ITERATIONS;
uniform float THRESHOLD;
uniform vec2 WINDOW_DIMENSIONS;
uniform float scaleFactor;
uniform vec2 originWindowCoords;

void main() {
    vec2 c = (gl_FragCoord.xy - originWindowCoords) / scaleFactor;
    vec2 z = vec2(0.0, 0.0);

    int iterationCount = 0;
    while (length(z) <= THRESHOLD && iterationCount < MAX_ITERATIONS) {
        for (int i = 0; i < P - 1; i++)
            z = vec2(z.x * z.x - z.y * z.y, 2 * z.x * z.y);
        z += c;
        iterationCount++;
    }

    FragColor = COLOURS[iterationCount % 128];
}