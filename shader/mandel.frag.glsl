#version 330 core
out vec4 FragColor;

uniform vec4 COLOURS[128];
uniform int MAX_ITERATIONS = 128;

uniform float threshold;
uniform float scaleFactor;
uniform vec2 originWindowCoords;
uniform float p;

vec2 complex_pow(vec2 a, float n) {
    float arg = atan(a.y, a.x);
    float modulus = length(a);
    float re = pow(modulus, n) * cos(n * arg);
    float im = pow(modulus, n) * sin(n * arg);
    return vec2(re, im);
}

void main() {
    vec2 c = (gl_FragCoord.xy - originWindowCoords) / scaleFactor;
    vec2 z = vec2(0.0, 0.0);

    int iterationCount = 0;
    while (length(z) <= threshold && iterationCount < MAX_ITERATIONS) {
        z = complex_pow(z, p) + c;
        iterationCount++;
    }

    FragColor = COLOURS[iterationCount % 128];
}