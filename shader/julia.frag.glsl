#version 330 core
out vec4 FragColor;

uniform vec4 COLOURS[128];
uniform int MAX_ITERATIONS = 128;

uniform float threshold;
uniform float scaleFactor;
uniform vec2 originWindowCoords;

uniform float p;

uniform float root;
uniform float realCoefficient;
uniform float imaginaryCoefficient;

uniform vec2 c;

vec2 complexPow(vec2 complexNum, float exponent) {
    float sqrMagnitude = dot(complexNum, complexNum);
    float sqrMagnitudeToPower = pow(sqrMagnitude, exponent / root);
    float arg = atan(complexNum.y, complexNum.x);
    float exparg = exponent * arg;
    float re = sqrMagnitudeToPower * cos(exparg);
    float im = sqrMagnitudeToPower * sin(exparg);
    return vec2(realCoefficient * re, imaginaryCoefficient * im);
}

void main() {
    vec2 z = (gl_FragCoord.xy - originWindowCoords) / scaleFactor;

    int iterationCount = 0;
    while (dot(z, z) <= threshold && iterationCount < MAX_ITERATIONS) {
        z = complexPow(z, p) + c;
        iterationCount++;
    }

    FragColor = COLOURS[iterationCount % 128];
}