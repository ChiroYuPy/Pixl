//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_MATERIAL_H
#define PIXLENGINE_MATERIAL_H

#include "Pixl/Rendering/Objects/Shader.h"
#include <unordered_map>

namespace Pixl {

    class Material {
    public:
        explicit Material(Ref<Shader> shader);
        virtual ~Material() = default;

        void bind() const;
        void unbind() const;

        Ref<Shader> getShader() const { return m_shader; }

    private:
        Ref<Shader> m_shader;
    };

    class MaterialFactory {
    public:
        static Ref<Material> createFromSource(const std::string& vertexSource, const std::string& fragmentSource);
    };

}

namespace Pixl {

}

#endif //PIXLENGINE_MATERIAL_H
