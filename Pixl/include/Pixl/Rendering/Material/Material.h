//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_MATERIAL_H
#define PIXLENGINE_MATERIAL_H

#include "Pixl/Rendering/Objects/Shader.h"

namespace Pixl {

    class Material {
    public:
        explicit Material(Ref<Shader> shader) : m_shader(std::move(shader)) {}
        virtual ~Material() = default;

        virtual void bind() const { m_shader->bind(); };
        virtual void unbind() const { m_shader->unbind(); };
        Ref<Shader> getShader() const { return m_shader; }

    protected:
        Ref<Shader> m_shader;
    };

}

#endif //PIXLENGINE_MATERIAL_H
