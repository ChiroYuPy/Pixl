//
// Created by ChiroYuki on 03/08/2025.
//

#include "Pixl/Rendering/Mesh/MultiMaterialMesh.h"

namespace Pixl {

    MultiMaterialMesh::SubMesh::SubMesh(Pixl::Ref<Pixl::IMaterial> mat, uint32_t offset, uint32_t count,
                                              uint32_t base)
            : material(std::move(mat)), indexOffset(offset), indexCount(count), baseVertex(base) {}

    MultiMaterialMesh::MultiMaterialMesh(Pixl::Ref<Pixl::IGeometry> geometry)
            : BaseMesh(std::move(geometry)) {}

    void MultiMaterialMesh::render(const glm::mat4 &transform, const glm::mat4 &viewProjection) const {
        m_geometry->bind();

        for (const auto &subMesh: m_subMeshes) {
            subMesh.material->bind();
            subMesh.material->getShader().setMat4("u_viewProjection", viewProjection);
            subMesh.material->getShader().setMat4("u_transform", transform);

            RenderCommand::DrawIndexed(m_drawMode, subMesh.indexCount,
                                       subMesh.indexOffset, subMesh.baseVertex);
            subMesh.material->unbind();
        }

        m_geometry->unbind();
    }

    const char *MultiMaterialMesh::getTypeName() const {
        return "MultiMaterialMesh";
    }

    void
    MultiMaterialMesh::addSubMesh(Pixl::Ref<Pixl::IMaterial> material, uint32_t indexOffset, uint32_t indexCount,
                                        uint32_t baseVertex) {
        m_subMeshes.emplace_back(std::move(material), indexOffset, indexCount, baseVertex);
    }

    size_t MultiMaterialMesh::getSubMeshCount() const {
        return m_subMeshes.size();
    }

    const MultiMaterialMesh::SubMesh &Pixl::MultiMaterialMesh::getSubMesh(size_t index) const {
        return m_subMeshes[index];
    }

}