//
// Created by ChiroYuki on 02/08/2025.
//

#ifndef PIXLENGINE_GEOMETRY_H
#define PIXLENGINE_GEOMETRY_H

#include <cstdint>

namespace Pixl {

    class Geometry {
    public:
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual uint32_t getIndexCount() const = 0;
        virtual ~Geometry() = default;
    };

}

#endif //PIXLENGINE_GEOMETRY_H
