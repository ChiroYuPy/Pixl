//
// Created by ChiroYuki on 07/08/2025.
//

#ifndef PIXLENGINE_RESOURCEMANAGER_H
#define PIXLENGINE_RESOURCEMANAGER_H

#include "IResourceLoader.h"
#include "Resource.h"

namespace Pixl {

    template<typename R>
    class ResourceManager {
    public:
        explicit ResourceManager(std::shared_ptr<IResourceLoader<R>> loader)
        : m_loader(loader) {}

        ~ResourceManager() = default;

        std::optional<Ref<R>> get(const std::string& absolutePath) {
            std::lock_guard<std::mutex> lock(mutex_);

            auto it = m_cache.find(absolutePath);
            if (it != m_cache.end()) {
                if (auto ptr = it->second.lock())
                    return ptr;
            }

            auto loaded = m_loader->load(absolutePath);
            if (!loaded.has_value()) {
                std::cerr << "Erreur : Impossible de charger la ressource '" << absolutePath << "'\n";
                return std::nullopt;
            }
            m_cache[absolutePath] = *loaded;
            return *loaded;
        }

        void clear() {
            std::lock_guard<std::mutex> lock(mutex_);
            m_cache.clear();
        }

    private:
        std::unordered_map<std::string, std::weak_ptr<R>> m_cache;
        Ref<IResourceLoader<R>> m_loader;
        std::mutex mutex_;
    };

}

#endif //PIXLENGINE_RESOURCEMANAGER_H
