//
// Created by ChiroYuki on 02/08/2025.
//

#include "Pixl/Rendering/Mesh/Mesh.h"

namespace Pixl {

    Mesh::Mesh(Ref<Geometry> geom, Ref<Material> mat)
    : m_geometry(std::move(geom)), m_material(std::move(mat)) {}

    void Mesh::render(glm::mat4 transform, const glm::mat4& viewProjection) const {
        m_material->bind(); // shader bind
        m_material->getShader().setMat4("u_viewProjection", viewProjection);
        m_material->getShader().setMat4("u_transform", transform);

        m_geometry->bind(); // vao bind

        uint32_t indexCount = m_geometry->getIndexCount();
        RenderCommand::DrawIndexed(DrawMode::Triangles, indexCount, 0);

        m_geometry->unbind(); // vao unbind

        m_material->unbind(); // shader unbind
    }

}