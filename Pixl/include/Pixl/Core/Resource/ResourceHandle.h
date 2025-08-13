//
// Created by ChiroYuki on 13/08/2025.
//

#ifndef PIXLENGINE_RESOURCEHANDLE_H
#define PIXLENGINE_RESOURCEHANDLE_H

#include "Pixl/Core/Base.h"

namespace Pixl {

    template<typename T>
    class ResourceHandle {
    public:
        ResourceHandle() = default;
        explicit ResourceHandle(Ref<T> res) : resource(res) {}

        T* get() const { return resource.get(); }
        T* operator->() const { return resource.get(); }
        T& operator*() const { return *resource.get(); }
        [[nodiscard]] bool valid() const { return resource != nullptr && resource->isValid(); }

        explicit operator bool() const { return valid(); }

        void reset() { resource.reset(); }

    private:
        Ref<T> resource;
    };

}

#endif //PIXLENGINE_RESOURCEHANDLE_H
