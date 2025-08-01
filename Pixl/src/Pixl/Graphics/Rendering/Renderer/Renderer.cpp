//
// Created by ChiroYuki on 01/08/2025.
//

#include "Pixl/Graphics/Rendering/Renderer/Renderer.h"
#include "Pixl/Graphics/Rendering/Objects/VertexArray.h"
#include "Pixl/Graphics/Rendering/RenderCommand.h"
#include "Pixl/Graphics/Rendering/Camera/ICamera.h"

namespace Pixl {

    Scope<Renderer::SceneData> Renderer::s_sceneData = MakeScope<SceneData>();

    void Renderer::Init() {
        RenderCommand::Init();
        // Renderer2D::Init();
    }

    void Renderer::Shutdown() {
        // Renderer2D::Shutdown();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::SetViewport(0, 0, width, height);
        s_sceneData->aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    }

    void Renderer::beginFrame(ICamera& camera) {
        camera.setAspectRatio(s_sceneData->aspectRatio);
        const glm::mat4 proj = camera.getProjectionMatrix();
        const glm::mat4 view = camera.getViewMatrix();
        s_sceneData->viewProjMatrix = proj * view;
    }

    void Renderer::endFrame() {
        //TODO: idk
    }

    void Renderer::Submit(const Ref <Shader> &shader, const Ref <VertexArray> &vertexArray, const glm::mat4 &transform) {
        shader->bind();
        shader->setMat4("u_viewProjection", s_sceneData->viewProjMatrix);
        shader->setMat4("u_transform", transform);

        vertexArray->bind();
        RenderCommand::DrawArrays(vertexArray, DrawMode::Triangles, 3);
    }
}