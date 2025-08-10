//
// Created by ChiroYuki on 09/08/2025.
//

#ifndef PIXLENGINE_SYSTEMMANAGER_H
#define PIXLENGINE_SYSTEMMANAGER_H

#include "Pixl/Core/Base.h"
#include "Pixl/Core/ECS/ISystem.h"
#include "Pixl/Core/Time/Time.h"

#include <vector>

namespace Pixl {

    class SystemManager {
    public:
        SystemManager() = default;

        template<typename T, typename... Args>
        void add(Args&&... args) {
            static_assert(std::is_base_of_v<ISystem, T>, "T must inherit from ISystem");

            auto system = MakeScope<T>(std::forward<Args>(args)...);
            systems.emplace_back(std::move(system));
        }

        void update(Scene& scene, Time dt) {
            for (auto& system : systems)
                system->update(scene, dt);
        }

    private:
        std::vector<Scope<ISystem>> systems;
    };

}

#endif //PIXLENGINE_SYSTEMMANAGER_H
