//
// Created by ChiroYuki on 13/08/2025.
//

#ifndef PIXLENGINE_TEXTURE_H
#define PIXLENGINE_TEXTURE_H

#include "Pixl/Core/Resource/Resource.h"

#include <glad/glad.h>
#include <utility>
#include <iostream>
#include <functional>
#include <typeindex>

namespace Pixl {

    class Texture : public IResource {
    public:
        GLuint textureId = 0;
        int width = 0, height = 0, channels = 0;
        GLenum format = GL_RGB;
        GLenum internalFormat = GL_RGB;

        Texture() = default;

        Texture(GLuint id, int w, int h, int c, GLenum fmt, GLenum intFmt);

        void cleanup() override;

        [[nodiscard]] bool isValid() const override;

        void bind(int unit = 0) const;

        void setWrapMode(GLenum wrapS, GLenum wrapT) const;

        void setFilterMode(GLenum minFilter, GLenum magFilter) const;
    };

}

#endif //PIXLENGINE_TEXTURE_H
