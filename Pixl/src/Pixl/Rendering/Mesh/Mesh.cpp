//
// Created by ChiroYuki on 02/08/2025.
//

#include <utility>

#include "Pixl/Rendering/Mesh/Mesh.h"

namespace Pixl {

    Mesh::Mesh(Ref<Geometry> geometry, Ref<Material> material)
    : m_geometry(std::move(geometry)), m_material(std::move(material)) {}

    void Mesh::render(const glm::mat4& viewProjection) const {
        if (!m_geometry || !m_material) return;

        m_material->bind();

        auto shader = m_material->getShader();
        if (shader) {
            shader->setMat4("u_viewProjection", viewProjection); //TODO: to move
            shader->setMat4("u_transform", m_transform);
        }

        m_geometry->bind();

        if (m_geometry->hasIndices()) {
            RenderCommand::DrawIndexed(DrawMode::Triangles, m_geometry->getIndexCount(), 0, 0);
        } else {
            RenderCommand::DrawArrays(DrawMode::Triangles, 0, m_geometry->getVertexCount());
        }

        m_geometry->unbind();

        m_material->unbind();
    }

}