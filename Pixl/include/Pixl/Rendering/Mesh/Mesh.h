//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_MESH_H
#define PIXLENGINE_MESH_H

#include "Pixl/Rendering/Material/Material.h"
#include "Pixl/Rendering/Geometry/Geometry.h"
#include "Pixl/Rendering/RenderCommand.h"

#include <utility>

namespace Pixl {

    class Mesh {
    public:
        Mesh() = default;
        Mesh(Ref<Geometry> geometry, Ref<Material> material);
        ~Mesh() = default;

        void setGeometry(Ref<Geometry> geometry) { m_geometry = std::move(geometry); }
        void setMaterial(Ref<Material> material) { m_material = std::move(material); }

        Ref<Geometry> getGeometry() const { return m_geometry; }
        Ref<Material> getMaterial() const { return m_material; }

        void setTransform(const glm::mat4& transform) { m_transform = transform; }
        const glm::mat4& getTransform() const { return m_transform; }

        void render(const glm::mat4& viewProjection) const;

    private:
        Ref<Geometry> m_geometry;
        Ref<Material> m_material;
        glm::mat4 m_transform = glm::mat4(1.0f);
    };

}

#endif //PIXLENGINE_MESH_H
