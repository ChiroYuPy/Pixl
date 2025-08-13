//
// Created by ChiroYuki on 13/08/2025.
//

#include "Pixl/Rendering/Objects/Texture.h"

namespace Pixl {

    Texture::Texture(GLuint id, int w, int h, int c, GLenum fmt, GLenum intFmt)
            : textureId(id), width(w), height(h), channels(c), format(fmt), internalFormat(intFmt) {}

    void Texture::cleanup() {
        if (textureId != 0) {
            glDeleteTextures(1, &textureId);
            textureId = 0;
            width = height = channels = 0;
        }
    }

    bool Texture::isValid() const { return textureId != 0; }

    void Texture::bind(int unit) const {
        if (isValid()) {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, textureId);
        }
    }

    void Texture::setWrapMode(GLenum wrapS, GLenum wrapT) const {
        if (isValid()) {
            glBindTexture(GL_TEXTURE_2D, textureId);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrapS));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrapT));
        }
    }

    void Texture::setFilterMode(GLenum minFilter, GLenum magFilter) const {
        if (isValid()) {
            glBindTexture(GL_TEXTURE_2D, textureId);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(minFilter));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(magFilter));
        }
    }

}