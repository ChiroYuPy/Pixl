//
// Created by ChiroYuki on 03/08/2025.
//

#ifndef PIXLENGINE_VERTEXATTRIBUTETYPE_H
#define PIXLENGINE_VERTEXATTRIBUTETYPE_H

#include <cstdint>

namespace Pixl {

    enum class VertexAttributeType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t ShaderDataTypeSize(VertexAttributeType type) {
        switch (type)
        {
            case VertexAttributeType::Float:    return 4;
            case VertexAttributeType::Float2:   return 4 * 2;
            case VertexAttributeType::Float3:   return 4 * 3;
            case VertexAttributeType::Float4:   return 4 * 4;
            case VertexAttributeType::Mat3:     return 4 * 3 * 3;
            case VertexAttributeType::Mat4:     return 4 * 4 * 4;
            case VertexAttributeType::Int:      return 4;
            case VertexAttributeType::Int2:     return 4 * 2;
            case VertexAttributeType::Int3:     return 4 * 3;
            case VertexAttributeType::Int4:     return 4 * 4;
            case VertexAttributeType::Bool:     return 1;
            case VertexAttributeType::None:     break;
        }

        return 0;
    }

}

#endif //PIXLENGINE_VERTEXATTRIBUTETYPE_H
