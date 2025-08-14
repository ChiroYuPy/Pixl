//
// Created by ChiroYuki on 09/08/2025.
//

#include "layers/EnttTestLayer.h"
#include "Pixl/Components/TransformComponent.h"
#include "Pixl/Components/MeshComponent.h"
#include "Pixl/Utils/PrefabRegistery.h"

#include <random>

void EnttTestLayer::onAttach() {
    auto& scene = Pixl::Application::get().createScene("TestScene");

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distPos(-8.f, 8.f);
    std::uniform_real_distribution<float> distScale(1.0f, 2.f);
    std::uniform_real_distribution<float> distAngle(0.f, glm::two_pi<float>());
    std::uniform_int_distribution<int> distShape(0, 2); // 0=cube,1=sphere,2=plane

    constexpr unsigned int objectCount = 16;
    for (int i = 0; i < objectCount; ++i) {
        // Choisir une forme aléatoire
        int shapeType = distShape(gen);
        entt::entity entity;
        switch (shapeType) {
            case 0: entity = Pixl::PrefabRegistry::create(scene.getRegistry(), "cube"); break;
            case 1: entity = Pixl::PrefabRegistry::create(scene.getRegistry(), "sphere"); break;
            case 2: entity = Pixl::PrefabRegistry::create(scene.getRegistry(), "plane"); break;
        }

        auto* transform = scene.getComponent<Pixl::TransformComponent>(entity);

        transform->position = {distPos(gen), distPos(gen), distPos(gen)};

        float scaleValue = distScale(gen);
        transform->scale = {scaleValue, scaleValue, scaleValue};

        float angle = distAngle(gen);
        glm::vec3 axis = glm::normalize(glm::vec3(distPos(gen), distPos(gen), distPos(gen)));
        transform->rotation = glm::angleAxis(angle, axis);

        transform->isDirty = true;
    }
}

void EnttTestLayer::onDetach() {

}

void EnttTestLayer::onUpdate(Pixl::Time &deltaTime) {

}

void EnttTestLayer::onEvent(Pixl::Event &event) {

}