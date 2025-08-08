//
// Created by ChiroYuki on 08/08/2025.
//

#include "layers/HueExempleLayer.h"

void HueExempleLayer::onAttach() {
    m_totalTime = 0.0f;


    const std::string vertexSrc = R"(
#version 330 core
out vec2 vUV;
void main()
{
    vec2 positions[3] = vec2[](vec2(-1.0, -1.0), vec2(3.0, -1.0), vec2(-1.0, 3.0));
    gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);
    vUV = positions[gl_VertexID] * 0.5 + 0.5;
}
)";

    const std::string fragmentSrc = R"(
#version 330 core
in vec2 vUV;
out vec4 FragColor;

uniform float u_time;

// Conversion HSV vers RGB
vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    // Coordonnées centrées
    vec2 uv = vUV - 0.5;

    // Distance du centre
    float distance = length(uv);

    // Calcul de la teinte basée sur la distance + animation temporelle
    float hue = distance * 2.0 + u_time * 0.5;

    // Garder la valeur entre 0 et 1
    hue = fract(hue);

    // Saturation et luminosité constantes
    float saturation = 1.0;
    float brightness = 1.0;

    // Conversion HSV vers RGB
    vec3 color = hsv2rgb(vec3(hue, saturation, brightness));

    FragColor = vec4(color, 1.0);
}
)";

    shader = Pixl::MakeRef<Pixl::Shader>();
    shader->loadFromSource(vertexSrc, fragmentSrc);

}

void HueExempleLayer::onDetach() {

}

void HueExempleLayer::onUpdate(Pixl::Time &deltaTime) {
    Pixl::RenderCommand::Clear();

    m_totalTime += deltaTime.asSeconds();

    shader->bind();
    shader->setFloat("u_time", m_totalTime);
    Pixl::RenderCommand::DrawArrays(Pixl::DrawMode::Triangles, 0, 3);
    shader->unbind();

}

void HueExempleLayer::onEvent(Pixl::Event &event) {

}