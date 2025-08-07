//
// Created by ChiroYuki on 07/08/2025.
//

#ifndef PIXLENGINE_CAMERATESTLAYER_H
#define PIXLENGINE_CAMERATESTLAYER_H

#include "Pixl/Pixl.h"

const std::string CUBE_VERT = R"(
        #version 330 core

        layout(location = 0) in vec3 a_position;

        uniform mat4 u_viewProjection;
        uniform mat4 u_transform;

        void main()
        {
            gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
        }
    )";

const std::string CUBE_FRAG = R"(
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

class CameraTestLayer : public Pixl::Layer {
public:
    void onAttach() override;
    void onDetach() override;
    void onUpdate(Pixl::Time& dt) override;
    void onEvent(Pixl::Event& e) override;

private:
    Pixl::Scope<Pixl::PerspectiveCamera>  camera;
    Pixl::Scope<Pixl::OrbitController>    cameraController;
    Pixl::Ref<Pixl::Mesh>                 mesh;
};

#endif //PIXLENGINE_CAMERATESTLAYER_H
