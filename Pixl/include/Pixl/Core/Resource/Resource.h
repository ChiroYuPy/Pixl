//
// Created by ChiroYuki on 07/08/2025.
//

#ifndef PIXLENGINE_RESOURCE_H
#define PIXLENGINE_RESOURCE_H

#include "Pixl/Core/Base.h"

#include <string>

namespace Pixl {

    class IResource {
    public:
        virtual ~IResource() = default;
        virtual void cleanup() = 0;
        [[nodiscard]] virtual bool isValid() const = 0;

        std::string path;
        size_t refCount = 0;
        bool persistent = false;
    };

}

#endif //PIXLENGINE_RESOURCE_H
