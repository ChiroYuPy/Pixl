//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_MESH_H
#define PIXLENGINE_MESH_H

#include <utility>

#include "Pixl/Core/Base.h"
#include "Pixl/Rendering/Geometry/Geometry.h"
#include "Pixl/Rendering/Material/Material.h"
#include "Pixl/Rendering/RenderCommand.h"

namespace Pixl {

    class Mesh {
    private:
        Ref<Geometry> m_geometry;
        Ref<Material> m_material;
        DrawMode m_drawMode;

    public:
        Mesh(Ref<Geometry> geom, Ref<Material> mat);

        void render(glm::mat4 transform, const glm::mat4& viewProjection) const;

        void setDrawMode(DrawMode mode);
        [[nodiscard]] DrawMode getDrawMode() const;
    };

}

#endif //PIXLENGINE_MESH_H
