/*
 *  Simple fragment sharder for Example 10
 */

#version 330 core

in vec3 normal;
in vec3 position;
in vec2 tc;
uniform samplerCube tex;
uniform vec4 colour;
uniform vec3 Eye;
uniform vec3 light;
uniform vec4 material;
out vec4 FragColor;

void main() {
    vec3 reflectTex, refractTex, N,E,L;
    float R0, cosTheta, r;
    R0 = 3/2;

	N = normalize(normal);
    E = normalize(Eye);
    L = normalize(position - Eye);

    reflectTex = reflect(L, N);
    refractTex = refract(L, N, R0);

    cosTheta = dot(E, N);
    r = R0 + (1.0 - R0) * pow(1.0 - cosTheta, 5.0);

    FragColor = r * texture(tex, reflectTex) + (1 - r) * texture(tex, refractTex);

}