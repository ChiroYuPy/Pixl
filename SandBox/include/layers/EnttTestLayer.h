//
// Created by ChiroYuki on 09/08/2025.
//

#ifndef PIXLENGINE_ENTTTESTLAYER_H
#define PIXLENGINE_ENTTTESTLAYER_H

#include "Pixl/Pixl.h"

#include <entt/entt.hpp>

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

    out vec4 frag_color;

    void main() {
        // Couleur rouge fixe pour le debug
        frag_color = vec4(1.0, 0.0, 0.0, 1.0);
    }
    )";

class EnttTestLayer : public Pixl::Layer {
public:
    void onAttach() override;
    void onDetach() override;
    void onUpdate(Pixl::Time& deltaTime) override;
    void onEvent(Pixl::Event& event) override;

private:
    Pixl::Ref<Pixl::Material> m_material;
    Pixl::Ref<Pixl::Geometry> m_geometry;
};

#endif //PIXLENGINE_ENTTTESTLAYER_H
