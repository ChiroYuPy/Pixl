//
// Created by ChiroYuki on 08/08/2025.
//

#include "layers/AnimationTransformTestLayer.h"

static float easeInOut(float t) {
    return t < 0.5f
           ? 2.0f * t * t
           : -1.0f + (4.0f - 2.0f * t) * t;
}

void AnimationTransformTestLayer::onAttach() {
    Pixl::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});

    float ar = Pixl::Application::get().getWindow().getAspectRatio();
    camera = Pixl::MakeScope<Pixl::PerspectiveCamera>(90.f, ar, 0.1f, 10000.f);
    camera->setPosition({0, 2, 2});
    camera->lookAt({0, 0, 0});

    auto geo = Pixl::Geometry::createCube();
    auto mat = Pixl::MaterialFactory::createFromSource(CUBE_VERT_A, CUBE_FRAG_A);
    mat->setProperty("u_color", glm::vec4(1.f, 0.1f, 0.2f, 1.f));
    mesh = Pixl::MakeScope<Pixl::Mesh>(geo, mat);

    elapsedTime = 0.0f;
}

void AnimationTransformTestLayer::onDetach() {

}

glm::mat4 AnimationTransformTestLayer::computeAnimatedTransform(float t) {
    // Appliquer easing
    float easedT = easeInOut(t);

    // Translation x de -2 à +2 avec easing
    float xPos = glm::mix(-2.4f, 2.4f, easedT);

    // Rotation Y de 0 à 360° avec easing
    float angle = glm::mix(0.0f, glm::radians(360.0f), easedT);

    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, glm::vec3(xPos, 0.0f, 0.0f));
    transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, -1.0f));

    return transform;
}

void AnimationTransformTestLayer::onUpdate(Pixl::Time &deltaTime) {
    elapsedTime += deltaTime.asSeconds();

    glm::mat4 projMatrix = camera->getProjectionMatrix();
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 viewProj = projMatrix * viewMatrix;

    float duration = 3.f;
    float t = fmod(elapsedTime, duration) / duration;

    glm::mat4 transform = computeAnimatedTransform(t);

    mesh->setTransform(transform);
    mesh->render(viewProj);
}

void AnimationTransformTestLayer::onEvent(Pixl::Event &event) {

}
