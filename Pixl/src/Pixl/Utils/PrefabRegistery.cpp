//
// Created by ChiroYuki on 12/08/2025.
//

#include "Pixl/Utils/PrefabRegistery.h"
#include "Pixl/Components/TransformComponent.h"
#include "Pixl/Components/MeshComponent.h"

namespace Pixl {

    std::unordered_map<std::string, PrefabCreator> PrefabRegistry::registry;

    void PrefabRegistry::registerPrefab(const std::string& name, PrefabCreator creator) {
        registry[name] = std::move(creator);
    }

    entt::entity PrefabRegistry::create(entt::registry& reg, const std::string& name) {
        auto it = registry.find(name);
        if (it != registry.end()) {
            return it->second(reg);
        }
        throw std::runtime_error("Prefab not found: " + name);
    }

    void PrefabRegistry::init() {
        registerPrefab("cube", [](entt::registry& reg) -> entt::entity {
            auto entity = reg.create();
            reg.emplace<TransformComponent>(entity);
            auto& mesh = reg.emplace<MeshComponent>(entity);
            mesh.geometry = GeometryFactory::createCube();
            mesh.material = MaterialFactory::createSolidColor();
            return entity;
        });
    }

}


//TODO: simple loading system, no centralisation ( loader + simple ressource without interface )