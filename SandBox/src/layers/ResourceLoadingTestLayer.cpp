//
// Created by ChiroYuki on 08/08/2025.
//

#include "layers/ResourceLoadingTestLayer.h"
#include "Pixl/Utils/Logger.h"

void ResourceLoadingTestLayer::onAttach() {
    auto& resourceService = Pixl::Application::get().getResourceService();

    auto texture = resourceService.getTexture("albedo.tpx");
    if (texture) Pixl::Logger::info("loading success !");
}

void ResourceLoadingTestLayer::onDetach() {

}

void ResourceLoadingTestLayer::onUpdate(Pixl::Time &deltaTime) {

}

void ResourceLoadingTestLayer::onEvent(Pixl::Event &event) {

}
