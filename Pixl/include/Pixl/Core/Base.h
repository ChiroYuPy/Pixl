//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_BASE_H
#define PIXLENGINE_BASE_H

#include <memory>

namespace Pixl {

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> MakeRef(Args&& ... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T, typename ... Args>
    constexpr Scope<T> MakeScope(Args&& ... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename Fn>
    auto MakeCallback(Fn fn) {
        return [fn](auto&&... args) -> decltype(auto) {
            return fn(std::forward<decltype(args)>(args)...);
        };
    }

    template<typename T, typename Fn>
    auto MakeMemberCallback(T* obj, Fn fn) {
        return [obj, fn](auto&&... args) -> decltype(auto) {
            return (obj->*fn)(std::forward<decltype(args)>(args)...);
        };
    }

    template <typename T> concept arithmetic = std::is_arithmetic_v<T>;
    template <typename T> concept floating_point = std::is_floating_point_v<T>;

}

#endif //PIXLENGINE_BASE_H
