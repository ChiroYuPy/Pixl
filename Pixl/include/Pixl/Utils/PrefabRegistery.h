//
// Created by ChiroYuki on 12/08/2025.
//

#ifndef PIXLENGINE_PREFABREGISTERY_H
#define PIXLENGINE_PREFABREGISTERY_H

#include <unordered_map>
#include <string>

#include "entt/entt.hpp"

namespace Pixl {

    using PrefabCreator = std::function<entt::entity(entt::registry&)>;

    class PrefabRegistry {
    public:
        static void registerPrefab(const std::string& name, PrefabCreator creator);
        static entt::entity create(entt::registry& reg, const std::string& name);
        static void init();

    private:
        static std::unordered_map<std::string, PrefabCreator> registry;
    };

}

#endif //PIXLENGINE_PREFABREGISTERY_H
