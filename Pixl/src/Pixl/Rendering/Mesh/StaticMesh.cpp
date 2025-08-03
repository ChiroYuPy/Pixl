//
// Created by ChiroYuki on 02/08/2025.
//

#include "Pixl/Rendering/Mesh/StaticMesh.h"

namespace Pixl {

    StaticMesh::StaticMesh(Ref<IGeometry> geometry, Ref<IMaterial> material)
    : BaseMesh(std::move(geometry)), m_material(std::move(material)) {}

    void StaticMesh::render(const glm::mat4& transform, const glm::mat4& viewProjection) const {
        // binding
        m_geometry->bind();
        m_material->bind();

        // set default uniforms
        m_material->getShader().setMat4("u_viewProjection", viewProjection);
        m_material->getShader().setMat4("u_transform", transform);

        // execute the draw command
        uint32_t indexCount = m_geometry->getIndexCount();
        RenderCommand::DrawIndexed(DrawMode::Triangles, indexCount, 0, 0);

        // unbinding
        m_material->unbind();
        m_geometry->unbind();
    }

    const char *StaticMesh::getTypeName() const {
        return "StaticMesh";
    }

    const IMaterial &StaticMesh::getMaterial() const {
        return *m_material;
    }

    void StaticMesh::setMaterial(Ref<IMaterial> material) {
        m_material = std::move(material);
    }

}