//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_STATICMESH_H
#define PIXLENGINE_STATICMESH_H

#include "Pixl/Rendering/Material/IMaterial.h"
#include "Pixl/Rendering/Mesh/BaseMesh.h"

#include <utility>

namespace Pixl {

    class StaticMesh : public BaseMesh {
    private:
        Ref<IMaterial> m_material;

    public:
        StaticMesh(Ref<IGeometry> geometry, Ref<IMaterial> material);

        void render(const glm::mat4& transform, const glm::mat4& viewProjection) const override;

        const char* getTypeName() const override;

        const IMaterial& getMaterial() const;
        void setMaterial(Ref<IMaterial> material);
    };

}

#endif //PIXLENGINE_STATICMESH_H
