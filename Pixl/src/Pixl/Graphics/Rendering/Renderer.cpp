//
// Created by ChiroYuki on 01/08/2025.
//

#include "Pixl/Graphics/Rendering/Renderer.h"
#include "Pixl/Graphics/Rendering/Objects/VertexArray.h"

namespace Pixl {

    void Renderer::Init() {
        // RenderCommand::Init();
        // Renderer2D::Init();
    }

    void Renderer::Shutdown() {
        // Renderer2D::Shutdown();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        // RenderCommand::SetViewport(0, 0, width, height);
    }

    // void Renderer::Begin(Camera &camera) {
    //     s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    // }

    void Renderer::EndScene() {
        //TODO: idk
    }

    void
    Renderer::Submit(const Ref <Shader> &shader, const Ref <VertexArray> &vertexArray, const glm::mat4 &transform) {
        shader->bind();
        shader->setMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->setMat4("u_Transform", transform);

        vertexArray->bind();
        // RenderCommand::DrawIndexed(vertexArray);
    }
}