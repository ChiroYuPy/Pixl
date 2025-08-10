//
// Created by ChiroYuki on 09/08/2025.
//

#include "layers/EnttTestLayer.h"
#include "Pixl/Components/Transform.h"

void EnttTestLayer::onAttach() {
    auto& scene = Pixl::Application::get().createScene("TestScene");

    auto entity = scene.createEntity();
    auto& transform = scene.addComponent<Pixl::Transform>(entity);
    transform.position = {1.0f, 2.0f, 3.0f};
    transform.isDirty = true;
}

void EnttTestLayer::onDetach() {

}

void EnttTestLayer::onUpdate(Pixl::Time &deltaTime) {

}

void EnttTestLayer::onEvent(Pixl::Event &event) {

}