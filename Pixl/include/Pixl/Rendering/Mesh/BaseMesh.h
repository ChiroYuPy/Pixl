//
// Created by ChiroYuki on 03/08/2025.
//

#ifndef PIXLENGINE_BASEMESH_H
#define PIXLENGINE_BASEMESH_H

#include "Pixl/Rendering/Mesh/IMesh.h"
#include "Pixl/Rendering/Geometry/IGeometry.h"

namespace Pixl {

    class BaseMesh : public IMesh {
    protected:
        Ref<IGeometry> m_geometry;
        DrawMode m_drawMode;

        // Cached bounds (calculated once)
        mutable bool m_boundsCalculated = false;
        mutable glm::vec3 m_boundsMin, m_boundsMax;

    public:
        BaseMesh(Ref<IGeometry> geometry, DrawMode mode = DrawMode::Triangles);

        // IMesh interface
        void setDrawMode(DrawMode mode) override;
        DrawMode getDrawMode() const override;

        bool hasBounds() const override;
        glm::vec3 getBoundsMin() const override;
        glm::vec3 getBoundsMax() const override;

    protected:
        virtual void calculateBounds() const;
    };

}

#endif //PIXLENGINE_BASEMESH_H
