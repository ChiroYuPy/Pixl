//
// Created by ChiroYuki on 03/08/2025.
//

#ifndef PIXLENGINE_MULTIMATERIALMESH_H
#define PIXLENGINE_MULTIMATERIALMESH_H

#include "BaseMesh.h"
#include "Pixl/Rendering/Material/IMaterial.h"

namespace Pixl {

    class MultiMaterialMesh : public BaseMesh {
    public:
        struct SubMesh {
            Ref<IMaterial> material;
            uint32_t indexOffset;
            uint32_t indexCount;
            uint32_t baseVertex;

            SubMesh(Ref<IMaterial> mat, uint32_t offset, uint32_t count, uint32_t base = 0);
        };

    private:
        std::vector<SubMesh> m_subMeshes;

    public:
        explicit MultiMaterialMesh(Ref<IGeometry> geometry);

        void render(const glm::mat4& transform, const glm::mat4& viewProjection) const override;

        const char* getTypeName() const override;

        // MultiMaterialMesh-specific methods
        void addSubMesh(Ref<IMaterial> material, uint32_t indexOffset, uint32_t indexCount, uint32_t baseVertex = 0);

        size_t getSubMeshCount() const;
        const SubMesh& getSubMesh(size_t index) const;
    };

}

#endif //PIXLENGINE_MULTIMATERIALMESH_H
