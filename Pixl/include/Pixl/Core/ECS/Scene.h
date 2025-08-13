//
// Created by ChiroYuki on 09/08/2025.
//

#ifndef PIXLENGINE_SCENE_H
#define PIXLENGINE_SCENE_H

#include <entt/entt.hpp>

namespace Pixl {

    class Scene {
    public:
        Scene(const std::string& sceneName) : name(sceneName) {}

        entt::entity createEntity() {
            return registry.create();
        }

        void destroyEntity(entt::entity entity) {
            registry.destroy(entity);
        }

        bool isEntityValid(entt::entity entity) const {
            return registry.valid(entity);
        }

        template<typename T>
        T& addComponent(entt::entity entity) {
            return registry.emplace<T>(entity);
        }

        template<typename T>
        T* getComponent(entt::entity entity) {
            if (!registry.valid(entity)) return nullptr;
            return registry.try_get<T>(entity);
        }

        template<typename T>
        bool hasComponent(entt::entity entity) const {
            return registry.valid(entity) && registry.all_of<T>(entity);
        }

        template<typename T>
        void removeComponent(entt::entity entity) {
            registry.remove<T>(entity);
        }

        entt::registry& getRegistry() {
            return registry;
        }

    private:
        entt::registry registry;
        std::string name;
    };

}

#endif //PIXLENGINE_SCENE_H
