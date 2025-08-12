#ifndef PIXLENGINE_VERTEXARRAY_H
#define PIXLENGINE_VERTEXARRAY_H

#include "Pixl/Core/Base.h"
#include "Pixl/Rendering/Objects/Buffer.h"
#include "Pixl/Rendering/Objects/VertexFormat.h"

namespace Pixl {

    class VertexArray {
    public:
        GLuint ID;

        VertexArray() {
            glGenVertexArrays(1, &ID);
            if (ID == 0)
                throw std::runtime_error("Failed to generate VAO");
        }

        ~VertexArray() {
            if (ID != 0)
                glDeleteVertexArrays(1, &ID);
        }

        void bind() const {
            glBindVertexArray(ID);
        }

        void unbind() const {
            glBindVertexArray(0);
        }

        // Configure les attributs en utilisant un VertexFormat et un VBO déjà liés
        void setVertexFormat(const VertexFormat& format, bool instanced = false, unsigned int divisor = 1) const {
            format.applyToVAO(instanced, divisor);
        }
    };

}

#endif //PIXLENGINE_VERTEXARRAY_H