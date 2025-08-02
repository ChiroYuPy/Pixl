//
// Created by ChiroYuki on 02/08/2025.
//

#include "Pixl/Rendering/Mesh/Mesh.h"

namespace Pixl {

    Mesh::Mesh(Ref<Geometry> geom, Ref<Material> mat)
            : m_geometry(std::move(geom)), m_material(std::move(mat)), m_drawMode(DrawMode::Triangles) {}

    void Mesh::render() const {
        m_material->bind(); // shader bind
        m_geometry->bind(); // vao bind

        uint32_t indexCount = m_geometry->getIndexCount();
        RenderCommand::DrawIndexed(m_drawMode, indexCount);

        m_geometry->unbind(); // vao unbind
        m_material->unbind(); // shader unbind
    }

    void Mesh::setDrawMode(DrawMode mode) {
        m_drawMode = mode;
    }

    DrawMode Mesh::getDrawMode() const {
        return m_drawMode;
    }

}