//
// Created by ChiroYuki on 08/08/2025.
//

#include "layers/AnimationTransformTestLayer.h"

void AnimationTransformTestLayer::onAttach() {
    Pixl::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});

    // Camera setup (fixed)
    float ar = Pixl::Application::get().getWindow().getAspectRatio();
    camera = Pixl::MakeScope<Pixl::PerspectiveCamera>(90.f, ar, 0.1f, 10000.f);
    camera->setPosition({3, 3, 3});
    camera->lookAt({0, 0, 0});

    // Cube & material setup
    auto geo = Pixl::Geometry::createCube();
    auto mat = Pixl::MaterialFactory::createFromSource(CUBE_VERT_A, CUBE_FRAG_A);
    mat->setProperty("u_color", glm::vec4(0.8f, 0.2f, 0.4f, 1.f));
    mesh = Pixl::MakeScope<Pixl::Mesh>(geo, mat);

    elapsedTime = 0.0f;
}

void AnimationTransformTestLayer::onDetach() {

}

void AnimationTransformTestLayer::onUpdate(Pixl::Time &deltaTime) {
    elapsedTime += deltaTime.asSeconds();

    Pixl::Renderer::beginFrame(*camera);

    glm::mat4 projMatrix = camera->getProjectionMatrix();
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 viewProj = projMatrix * viewMatrix;

    // Animation translation + rotation avec lerp sur le temps
    float duration = 5.0f; // durée d'un cycle complet en secondes
    float t = fmod(elapsedTime, duration) / duration; // t ∈ [0,1]

    // Translation : va de -2 à +2 sur x
    float xPos = glm::mix(-2.0f, 2.0f, t);

    // Rotation : rotation complète (360°) autour de Y
    float angle = glm::mix(0.0f, glm::radians(360.0f), t);

    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, glm::vec3(xPos, 0.0f, 0.0f));
    transform = glm::rotate(transform, angle, glm::vec3(0.0f, 1.0f, 0.0f));

    mesh->setTransform(transform);
    mesh->render(viewProj);

    Pixl::Renderer::endFrame();
}

void AnimationTransformTestLayer::onEvent(Pixl::Event &event) {

}
