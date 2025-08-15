//
// Created by ChiroYuki on 09/08/2025.
//

#include "layers/EnttTestLayer.h"
#include "Pixl/Utils/PrefabRegistery.h"
#include "Pixl/Components.h"
#include "Pixl/Utils/Logger.h"

#include <random>

void EnttTestLayer::onAttach() {
    auto& resourceService = Pixl::Application::get().getResourceService();
    auto toonMaterialOpt = resourceService.getMaterial("materials/ToonMaterial.json");
    if (!toonMaterialOpt.has_value()) {
        Pixl::Logger::error("ToonMaterial not loaded!");
        return;
    }
    auto toonMaterial = toonMaterialOpt.value();

    auto& scene = Pixl::Application::get().createScene("TestScene");

    constexpr int gridSize = 6;
    constexpr float spacing = 2.2f;
    constexpr float ballRadius = 0.45f;
    constexpr float bigBallRadius = 1.2f;

    float offset = (gridSize - 1) * spacing * 0.5f;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> colorDist(0.2f, 1.0f);

    int ballIndex = 0;
    const int totalBalls = gridSize * gridSize * gridSize;

    for (int x = 0; x < gridSize; ++x) {
        for (int y = 0; y < gridSize; ++y) {
            for (int z = 0; z < gridSize; ++z) {
                entt::entity entity = Pixl::PrefabRegistry::create(scene.getRegistry(), "sphere");

                auto* transform = scene.getComponent<Pixl::TransformComponent>(entity);

                transform->position = {
                        x * spacing - offset,
                        y * spacing + 8.0f,
                        z * spacing - offset
                };

                float scale = ballRadius * 2.0f;
                transform->scale = {scale, scale, scale};

                std::uniform_real_distribution<float> rotDist(0.0f, 2.0f * glm::pi<float>());
                glm::vec3 axis = glm::normalize(glm::vec3(
                        colorDist(gen) - 0.5f,
                        colorDist(gen) - 0.5f,
                        colorDist(gen) - 0.5f
                ));
                transform->rotation = glm::angleAxis(rotDist(gen), axis);

                transform->isDirty = true;

                auto& rigidBody = scene.addComponent<Pixl::RigidBodyComponent>(entity);
                std::uniform_real_distribution<float> massDist(0.8f, 1.2f);

                auto& collider = scene.addComponent<Pixl::ColliderComponent>(entity);
                collider.radius = ballRadius;

                auto* mesh = scene.getComponent<Pixl::MeshComponent>(entity);
                if (mesh) {
                    // Crée une nouvelle instance de Material à partir du shader du ToonMaterial
                    mesh->material = MakeRef<Pixl::Material>(toonMaterial->getShader());
                    // Si besoin, copier manuellement les propriétés du ToonMaterial ici
                    float hue = (float(ballIndex) / float(totalBalls)) * 360.0f;
                    auto hsvToRgb = [](float h, float s, float v) -> glm::vec3 {
                        float c = v * s;
                        float x = c * (1.0f - abs(fmod(h / 60.0f, 2.0f) - 1.0f));
                        float m = v - c;
                        glm::vec3 rgb;
                        if (h < 60) rgb = {c, x, 0};
                        else if (h < 120) rgb = {x, c, 0};
                        else if (h < 180) rgb = {0, c, x};
                        else if (h < 240) rgb = {0, x, c};
                        else if (h < 300) rgb = {x, 0, c};
                        else rgb = {c, 0, x};
                        return rgb + glm::vec3(m);
                    };
                    glm::vec3 color = hsvToRgb(hue, 0.8f + colorDist(gen) * 0.2f, 0.9f + colorDist(gen) * 0.1f);
                    mesh->material->setFloat3("u_color", color);
                }

                ballIndex++;
            }
        }
    }

    entt::entity bigBall = Pixl::PrefabRegistry::create(scene.getRegistry(), "sphere");
    auto* bigTransform = scene.getComponent<Pixl::TransformComponent>(bigBall);

    bigTransform->position = {
            0.0f,
            (gridSize - 1) * spacing + 15.0f,
            0.0f
    };

    float bigScale = bigBallRadius * 2.0f;
    bigTransform->scale = {bigScale, bigScale, bigScale};

    bigTransform->rotation = glm::quat(1, 0, 0, 0);
    bigTransform->isDirty = true;

    auto& bigRigidBody = scene.addComponent<Pixl::RigidBodyComponent>(bigBall);

    auto& bigCollider = scene.addComponent<Pixl::ColliderComponent>(bigBall);
    bigCollider.radius = bigBallRadius;

    auto* bigMesh = scene.getComponent<Pixl::MeshComponent>(bigBall);
    if (bigMesh && bigMesh->material) {
        bigMesh->material->setFloat3("u_color", {1.0f, 0.84f, 0.0f});
    }

    entt::entity groundEntity = Pixl::PrefabRegistry::create(scene.getRegistry(), "plane");
    auto* groundTransform = scene.getComponent<Pixl::TransformComponent>(groundEntity);
    groundTransform->position = {0, -0.1f, 0};
    groundTransform->scale = {40, 0, 40};

    auto* groundMesh = scene.getComponent<Pixl::MeshComponent>(groundEntity);
    if (groundMesh && groundMesh->material) {
        groundMesh->material->setFloat3("u_color", {0.7f, 0.7f, 0.75f});
    }

}

void EnttTestLayer::onDetach() {

}

void EnttTestLayer::onUpdate(Pixl::Time &deltaTime) {

}

void EnttTestLayer::onEvent(Pixl::Event &event) {

}