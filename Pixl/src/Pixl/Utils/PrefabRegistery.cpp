//
// Created by ChiroYuki on 12/08/2025.
//

#include "Pixl/Utils/PrefabRegistery.h"
#include "Pixl/Components/TransformComponent.h"
#include "Pixl/Components/MeshComponent.h"
#include "Pixl/Utils/Logger.h"

namespace Pixl {

    std::unordered_map<std::string, PrefabCreator> PrefabRegistry::registry;

    void PrefabRegistry::registerPrefab(const std::string& name, PrefabCreator creator) {
        if (creator) {
            registry[name] = std::move(creator);
            Logger::info("PrefabRegistry: Registered prefab '{}'", name);
        } else {
            Logger::warn("PrefabRegistry: Attempted to register null creator for '{}'", name);
        }
    }

    entt::entity PrefabRegistry::create(entt::registry& reg, const std::string& name) {
        auto it = registry.find(name);
        if (it != registry.end()) {
            try {
                auto entity = it->second(reg);
                Logger::debug("PrefabRegistry: Created entity from prefab '{}'", name);
                return entity;
            } catch (const std::exception& e) {
                Logger::error("PrefabRegistry: Error creating prefab '{}': {}", name, e.what());
                throw;
            }
        }

        Logger::error("PrefabRegistry: Prefab '{}' not found", name);
        throw std::runtime_error("Prefab not found: " + name);
    }

    bool PrefabRegistry::exists(const std::string& name) {
        return registry.find(name) != registry.end();
    }

    void PrefabRegistry::unregister(const std::string& name) {
        auto it = registry.find(name);
        if (it != registry.end()) {
            registry.erase(it);
            Logger::info("PrefabRegistry: Unregistered prefab '{}'", name);
        } else {
            Logger::warn("PrefabRegistry: Attempted to unregister unknown prefab '{}'", name);
        }
    }

    void PrefabRegistry::clear() {
        registry.clear();
        Logger::info("PrefabRegistry: Cleared all prefabs");
    }

    std::vector<std::string> PrefabRegistry::getRegisteredNames() {
        std::vector<std::string> names;
        names.reserve(registry.size());

        for (const auto& [name, _] : registry) {
            names.push_back(name);
        }

        return names;
    }

    void PrefabRegistry::init() {
        Logger::info("PrefabRegistry: Initializing default prefabs...");

        registerPrefab("cube", [](entt::registry& reg) -> entt::entity {
            auto entity = reg.create();
            reg.emplace<TransformComponent>(entity);

            auto& mesh = reg.emplace<MeshComponent>(entity);
            mesh.geometry = GeometryFactory::createCube();
            mesh.material = MaterialFactory::createSolidColor({1.f, 0.f, 0.f});

            return entity;
        });

        registerPrefab("sphere", [](entt::registry& reg) -> entt::entity {
            auto entity = reg.create();
            reg.emplace<TransformComponent>(entity);

            auto& mesh = reg.emplace<MeshComponent>(entity);
            mesh.geometry = GeometryFactory::createSphere();
            mesh.material = MaterialFactory::createSolidColor({0.f, 1.f, 0.f});

            return entity;
        });

        registerPrefab("plane", [](entt::registry& reg) -> entt::entity {
            auto entity = reg.create();
            reg.emplace<TransformComponent>(entity);

            auto& mesh = reg.emplace<MeshComponent>(entity);
            mesh.geometry = GeometryFactory::createPlane();
            mesh.material = MaterialFactory::createSolidColor({0.f, 0.f, 1.f});

            return entity;
        });

        Logger::info(std::format("PrefabRegistry: Initialized {} default prefabs", registry.size()));
    }

}


//TODO: simple loading system, no centralisation ( loader + simple ressource without interface )