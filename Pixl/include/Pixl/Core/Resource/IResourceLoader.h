//
// Created by ChiroYuki on 07/08/2025.
//

#ifndef PIXLENGINE_IRESOURCELOADER_H
#define PIXLENGINE_IRESOURCELOADER_H

#include "Pixl/Core/Base.h"

namespace Pixl {

    template<typename T>
    class IResourceLoader {
    public:
        virtual ~IResourceLoader() = default;
        virtual Ref<T> load(const std::string& logicalPath) = 0;
    };

}

#endif //PIXLENGINE_IRESOURCELOADER_H
