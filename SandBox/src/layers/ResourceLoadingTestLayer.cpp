//
// Created by ChiroYuki on 08/08/2025.
//

#include "layers/ResourceLoadingTestLayer.h"
#include "Pixl/Utils/Logger.h"

void ResourceLoadingTestLayer::onAttach() {
    auto& resourceService = Pixl::Application::get().getResourceService();

    auto texture = resourceService.getTexture("textures/albedo.json");
    if (texture) Pixl::Logger::info("texture loading success !");

    auto shader = resourceService.getShader("shaders/ColorUnlitShader.json");
    if (shader) Pixl::Logger::info("shader loading success !");
}

void ResourceLoadingTestLayer::onDetach() {

}

void ResourceLoadingTestLayer::onUpdate(Pixl::Time &deltaTime) {

}

void ResourceLoadingTestLayer::onEvent(Pixl::Event &event) {

}
