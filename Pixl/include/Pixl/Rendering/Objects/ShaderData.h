//
// Created by ChiroYuki on 03/08/2025.
//

#ifndef PIXLENGINE_SHADERDATA_H
#define PIXLENGINE_SHADERDATA_H

#include <cstdint>

namespace Pixl {

    enum class ComponentType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t ShaderDataTypeSize(ComponentType type) {
        switch (type)
        {
            case ComponentType::Float:    return 4;
            case ComponentType::Float2:   return 4 * 2;
            case ComponentType::Float3:   return 4 * 3;
            case ComponentType::Float4:   return 4 * 4;
            case ComponentType::Mat3:     return 4 * 3 * 3;
            case ComponentType::Mat4:     return 4 * 4 * 4;
            case ComponentType::Int:      return 4;
            case ComponentType::Int2:     return 4 * 2;
            case ComponentType::Int3:     return 4 * 3;
            case ComponentType::Int4:     return 4 * 4;
            case ComponentType::Bool:     return 1;
            case ComponentType::None:     break;
        }

        return 0;
    }

}

#endif //PIXLENGINE_SHADERDATA_H
