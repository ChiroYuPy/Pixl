//
// Created by ChiroYuki on 08/08/2025.
//

#include "layers/HueExempleLayer.h"

void HueExempleLayer::onAttach() {
    m_Hue = 0.0f;
}

void HueExempleLayer::onDetach() {

}

glm::vec3 HSVtoRGB(float h, float s, float v) {
    const float c = v * s;
    const float x = c * (1.0f - std::fabs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
    const float m = v - c;

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    if      (h <  60.0f) { r = c; g = x; }
    else if (h < 120.0f) { r = x; g = c; }
    else if (h < 180.0f) { g = c; b = x; }
    else if (h < 240.0f) { g = x; b = c; }
    else if (h < 300.0f) { r = x; b = c; }
    else                 { r = c; b = x; }

    return { r + m, g + m, b + m };
}

void HueExempleLayer::onUpdate(Pixl::Time &deltaTime) {
    Pixl::RenderCommand::Clear();

    m_Hue += 60.0f * deltaTime.asSeconds();
    if (m_Hue >= 360.0f)
        m_Hue -= 360.0f;

    const glm::vec3 rgb = HSVtoRGB(m_Hue, 1.0f, 1.0f);
    Pixl::RenderCommand::SetClearColor({ rgb.r, rgb.g, rgb.b, 1.0f });
}

void HueExempleLayer::onEvent(Pixl::Event &event) {

}