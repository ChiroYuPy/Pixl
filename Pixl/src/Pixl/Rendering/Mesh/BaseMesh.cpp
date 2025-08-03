//
// Created by ChiroYuki on 03/08/2025.
//

#include "Pixl/Rendering/Mesh/BaseMesh.h"

namespace Pixl {

    BaseMesh::BaseMesh(Ref<IGeometry> geometry, DrawMode mode)
            : m_geometry(std::move(geometry)), m_drawMode(mode) {}

    void BaseMesh::setDrawMode(DrawMode mode) { m_drawMode = mode; }

    DrawMode BaseMesh::getDrawMode() const { return m_drawMode; }

    bool BaseMesh::hasBounds() const { return true; }

    glm::vec3 BaseMesh::getBoundsMin() const {
        if (!m_boundsCalculated) calculateBounds();
        return m_boundsMin;
    }

    glm::vec3 BaseMesh::getBoundsMax() const {
        if (!m_boundsCalculated) calculateBounds();
        return m_boundsMax;
    }

    void BaseMesh::calculateBounds() const {
        // Implementation would extract bounds from geometry
        // This is a placeholder
        m_boundsMin = glm::vec3(-1.0f);
        m_boundsMax = glm::vec3(1.0f);
        m_boundsCalculated = true;
    }

}