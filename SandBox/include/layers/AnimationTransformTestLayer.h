//
// Created by ChiroYuki on 08/08/2025.
//

#ifndef PIXLENGINE_ANIMATIONTRANSFORMTESTLAYER_H
#define PIXLENGINE_ANIMATIONTRANSFORMTESTLAYER_H

#include "Pixl/Pixl.h"

const std::string CUBE_VERT_A = R"(
        #version 330 core

        layout(location = 0) in vec3 a_position;

        uniform mat4 u_viewProjection;
        uniform mat4 u_transform;

        void main()
        {
            gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
        }
    )";

const std::string CUBE_FRAG_A = R"(
        #version 330 core

        uniform vec4 u_color;
        uniform float u_metallic;
        uniform float u_roughness;
        uniform vec3 u_emissive;

        out vec4 frag_color;

        void main() {
            // Exemple d'utilisation des propriétés
            vec3 finalColor = u_color.rgb + u_emissive;
            finalColor = mix(finalColor, finalColor * 0.5, u_metallic);
            finalColor = mix(finalColor, finalColor * u_roughness, 0.2);

            frag_color = vec4(finalColor, u_color.a);
        }
    )";

class AnimationTransformTestLayer : public Pixl::Layer {
public:
    void onAttach() override;
    void onDetach() override;
    void onUpdate(Pixl::Time& deltaTime) override;
    void onEvent(Pixl::Event& event) override;

private:
    Pixl::Scope<Pixl::PerspectiveCamera> camera;
    Pixl::Scope<Pixl::Mesh> mesh;

    float elapsedTime = 0.0f;

    glm::mat4 computeAnimatedTransform(float t);
};

#endif //PIXLENGINE_ANIMATIONTRANSFORMTESTLAYER_H
