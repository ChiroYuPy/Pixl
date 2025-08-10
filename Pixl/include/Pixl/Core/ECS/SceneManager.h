//
// Created by ChiroYuki on 09/08/2025.
//

#ifndef PIXLENGINE_SCENEMANAGER_H
#define PIXLENGINE_SCENEMANAGER_H

#include "Pixl/Core/Base.h"
#include "Pixl/Core/ECS/Scene.h"

#include <string>

namespace Pixl {

    class SceneManager {
    public:
        SceneManager() {
            loadScene("mainScene");
        }

        Scene& loadScene(const std::string& name) {
            if (scenes.find(name) == scenes.end())
                scenes[name] = std::make_unique<Scene>(name);

            activeScene = scenes[name].get();
            return *activeScene;
        }

        Scene& getActiveScene() {
            if (!activeScene) {
                return loadScene("mainScene");
            }
            return *activeScene;
        }

        bool hasActiveScene() const {
            return activeScene != nullptr;
        }

    private:
        std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
        Scene* activeScene = nullptr;
    };

}

#endif //PIXLENGINE_SCENEMANAGER_H
