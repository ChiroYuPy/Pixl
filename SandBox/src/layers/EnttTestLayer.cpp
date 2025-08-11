//
// Created by ChiroYuki on 09/08/2025.
//

#include "layers/EnttTestLayer.h"
#include "Pixl/Components/TransformComponent.h"
#include "Pixl/Components/MeshComponent.h"

#include <random>

void EnttTestLayer::onAttach() {
    auto& scene = Pixl::Application::get().createScene("TestScene");

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distPos(-8.f, 8.f);
    std::uniform_real_distribution<float> distScale(1.0f, 2.f);
    std::uniform_real_distribution<float> distAngle(0.f, glm::two_pi<float>());


    m_material = Pixl::MaterialFactory::createFromSource(CUBE_VERT, CUBE_FRAG);
    m_geometry = Pixl::Geometry::createCube();


    for (int i = 0; i < 1000; ++i) {
        auto entity = scene.createEntity();
        auto& transform = scene.addComponent<Pixl::TransformComponent>(entity);
        auto& mesh = scene.addComponent<Pixl::MeshComponent>(entity);

        transform.position = {distPos(gen), distPos(gen), distPos(gen)};

        float scaleValue = distScale(gen);
        transform.scale = {scaleValue, scaleValue, scaleValue};

        float angle = distAngle(gen);
        glm::vec3 axis = glm::normalize(glm::vec3(distPos(gen), distPos(gen), distPos(gen)));
        transform.rotation = glm::angleAxis(angle, axis);

        transform.isDirty = true;

        mesh.geometry = m_geometry;
        mesh.material = m_material;
    }
}

void EnttTestLayer::onDetach() {

}

void EnttTestLayer::onUpdate(Pixl::Time &deltaTime) {

}

void EnttTestLayer::onEvent(Pixl::Event &event) {

}