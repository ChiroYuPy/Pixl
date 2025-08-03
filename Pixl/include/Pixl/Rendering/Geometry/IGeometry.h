//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_IGEOMETRY_H
#define PIXLENGINE_IGEOMETRY_H

#include <cstdint>

namespace Pixl {

    class IGeometry {
    public:
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual uint32_t getIndexCount() const = 0;
        virtual VertexLayout getVertexLayout() const = 0;
        virtual ~IGeometry() = default;
    };

}

#endif //PIXLENGINE_IGEOMETRY_H
