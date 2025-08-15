#version 330 core

out vec4 frag_color;

uniform vec3 u_color;
uniform float u_threshold;

void main() {
    float intensity = dot(u_color, vec3(0.299, 0.587, 0.114));
    float toon = intensity > u_threshold ? 1.0 : 0.5;
    frag_color = vec4(u_color * toon, 1.0);
}

