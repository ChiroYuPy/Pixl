//
// Created by ChiroYuki on 07/08/2025.
//

#ifndef PIXLENGINE_IRESOURCELOADER_H
#define PIXLENGINE_IRESOURCELOADER_H

#include "Pixl/Core/Base.h"

#include <optional>

namespace Pixl {

    template<typename R>
    class IResourceLoader {
    public:
        virtual ~IResourceLoader() = default;
        virtual std::optional<Ref<R>> load(const std::string& path) = 0;
    };

}

#endif //PIXLENGINE_IRESOURCELOADER_H
