//
// Created by ChiroYuki on 09/08/2025.
//

#include "Pixl/Systems/RenderSystem.h"
#include "Pixl/Rendering/Renderer/Renderer.h"
#include "Pixl/Rendering/RenderCommand.h"
#include "Pixl/Components/MeshComponent.h"

namespace Pixl {

    RenderSystem::RenderSystem() {}

    void RenderSystem::update(Scene &scene, Time deltaTime) {
        Pixl::RenderCommand::Clear();
        auto &registry = scene.getRegistry();
        auto view = registry.view<TransformComponent, MeshComponent>();

        for (auto entity : view) {
            auto [transform, mesh] = view.get<TransformComponent, MeshComponent>(entity);

            if (!mesh.visible || !mesh.geometry || !mesh.material) continue;

            const glm::mat4& transformMatrix = transform.worldMatrix;
            Renderer::submit(mesh.material, mesh.geometry, transformMatrix);
        }

        Renderer::flush();
    }

}