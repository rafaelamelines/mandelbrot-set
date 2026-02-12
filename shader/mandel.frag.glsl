#version 330 core
out vec4 FragColor;

uniform vec4 COLOURS[128];
uniform int MAX_ITERATIONS;
uniform float THRESHOLD;
uniform vec2 WINDOW_DIMENSIONS;
uniform float scaleFactor;
uniform vec2 originWindowCoords;

void main() {
    vec2 z_0 = (gl_FragCoord.xy - originWindowCoords) / scaleFactor;
    vec2 z_1 = vec2(0.0, 0.0);
    vec2 z_2 = vec2(0.0, 0.0);

    int iterationCount = 0;
    while ((z_2.x + z_2.y) <= THRESHOLD && iterationCount < MAX_ITERATIONS) {
        z_2 = vec2(z_1.x * z_1.x, z_1.y * z_1.y);
        z_1 = vec2(z_2.x - z_2.y + z_0.x, (z_1.x + z_1.x) * z_1.y + z_0.y);
        iterationCount++;
    }

    FragColor = COLOURS[iterationCount % 128];
}