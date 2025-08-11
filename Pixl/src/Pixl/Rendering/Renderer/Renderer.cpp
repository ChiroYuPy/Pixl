//
// Created by ChiroYuki on 01/08/2025.
//

#include <algorithm>
#include <iostream>
#include "Pixl/Rendering/Renderer/Renderer.h"
#include "Pixl/Rendering/Objects/VertexArray.h"
#include "Pixl/Rendering/RenderCommand.h"
#include "Pixl/Rendering/Camera/ICamera.h"

namespace Pixl {

    RenderStats Renderer::s_stats;
    Scope<Renderer::SceneData> Renderer::s_sceneData = MakeScope<SceneData>();
    std::vector<Renderer::RenderCommandData> Renderer::s_renderQueue;

    void Renderer::init() {
        RenderCommand::init();
        // Renderer2D::init();
    }

    void Renderer::shutdown() {
        // Renderer2D::shutdown();
    }

    void Renderer::onWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::SetViewport(0, 0, width, height);
        s_sceneData->aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    }

    void Renderer::setActiveCamera(const Ref<ICamera>& camera) {
        s_sceneData->camera = camera;
    }

    void Renderer::beginFrame() {

    }

    void Renderer::endFrame() {
        Geometry::unbind();
        Shader::unbind();

        auto stats = Pixl::Renderer::getStats();
        std::cout << "Draw Calls: " << stats.drawCalls << ", Triangles: " << stats.triangles << std::endl;
    }

    void Renderer::submit(const Ref<Material> &material, const Ref<Geometry> &geometry, const glm::mat4 &transform) {
        s_renderQueue.push_back({material, geometry, transform});
    }

    void Renderer::flush() {
        s_stats.reset();

        std::sort(s_renderQueue.begin(), s_renderQueue.end(),
                  [](const RenderCommandData& a, const RenderCommandData& b) {
                      return a.material->getShader()->getID() < b.material->getShader()->getID();
                  });

        uint32_t currentShaderID = 0;

        for (auto& cmd : s_renderQueue) {
            Ref<Shader> shader = cmd.material->getShader();

            if (shader->getID() != currentShaderID) {
                shader->bind();
                currentShaderID = shader->getID();

                const glm::mat4 proj = s_sceneData->camera->getProjectionMatrix();
                const glm::mat4 view = s_sceneData->camera->getViewMatrix();
                shader->setMat4("u_viewProjection", proj * view);
            }
            shader->setMat4("u_transform", cmd.transform);

            auto vertexArray = cmd.geometry->getVertexArray();
            if (vertexArray) {
                vertexArray->bind();

                if (cmd.geometry->hasIndices()) {
                    uint32_t indexCount = cmd.geometry->getIndexCount();
                    RenderCommand::DrawIndexed(DrawMode::Triangles, indexCount, 0, 0);

                    s_stats.triangles += indexCount / 3;
                } else {
                    uint32_t vertexCount = cmd.geometry->getVertexCount();
                    RenderCommand::DrawArrays(DrawMode::Triangles, 0, vertexCount);

                    s_stats.triangles += vertexCount / 3;
                }

                s_stats.drawCalls++;

                vertexArray->unbind();
            }
        }
        s_renderQueue.clear();
    }

}