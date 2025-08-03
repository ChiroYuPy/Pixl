//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_BASE_H
#define PIXLENGINE_BASE_H

#include <memory>

#define HZ_EXPAND_MACRO(x) x
#define HZ_STRINGIFY_MACRO(x) #x

constexpr int BIT(int x) {
    return 1 << x;
}

template<typename T, typename Fn>
constexpr auto makeMemberCallback(T* obj, Fn fn) {
    return [obj, fn](auto&&... args) -> decltype(auto) {
        return (obj->*fn)(std::forward<decltype(args)>(args)...);
    };
}

namespace Pixl {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> makeScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> makeRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    typedef uint32_t GL_ID;

}

#endif //PIXLENGINE_BASE_H
