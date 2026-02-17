#version 330 core
out vec4 FragColor;

uniform vec4 COLOURS[128];
uniform int MAX_ITERATIONS = 128;

uniform float threshold;
uniform float scaleFactor;
uniform vec2 originWindowCoords;
uniform int p;

void main() {
    vec2 c = (gl_FragCoord.xy - originWindowCoords) / scaleFactor;
    vec2 z = vec2(0.0, 0.0);

    int iterationCount = 0;
    while (length(z) <= threshold && iterationCount < MAX_ITERATIONS) {
        vec2 z_temp = z;
        for (int i = 0; i < p - 1; i++)
            z_temp = vec2(z_temp.x * z.x - z_temp.y * z.y, z_temp.x * z.y + z.x * z_temp.y);
        z_temp += c;
        z = z_temp;
        iterationCount++;
    }

    FragColor = COLOURS[iterationCount % 128];
}