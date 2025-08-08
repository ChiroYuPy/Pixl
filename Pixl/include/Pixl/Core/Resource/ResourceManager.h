//
// Created by ChiroYuki on 07/08/2025.
//

#ifndef PIXLENGINE_RESOURCEMANAGER_H
#define PIXLENGINE_RESOURCEMANAGER_H

#include "Pixl/Core/Application.h"
#include "ResourceCache.h"

namespace Pixl {

    class ResourceManager {
    public:
        template<typename T>
        void registerLoader(typename ResourceCache<T>::LoaderFunc loader) {
            auto typeIdx = std::type_index(typeid(T));
            m_caches[typeIdx] = std::make_unique<ResourceCache<T>>(std::move(loader));
        }

        template<typename T>
        Ref<T> getOrLoad(const std::string &name) {
            return getCache<T>().getOrLoad(name);
        }

        template<typename T>
        Ref<T> forceReload(const std::string &name) {
            return getCache<T>().forceReload(name);
        }

        template<typename T>
        Ref<T> get(const std::string &name) {
            return getCache<T>().get(name);
        }

        template<typename T>
        bool exists(const std::string &name) {
            return getCache<T>().exists(name);
        }

        template<typename T>
        void unload(const std::string &name) {
            getCache<T>().unload(name);
        }

        // Utilitaires pour la gestion globale
        void clearAll() {
            for (auto &[type, cache]: m_caches)
                cache->clear();
        }

        template<typename T>
        void clearType() {
            getCache<T>().clear();
        }

        template<typename T>
        size_t getLoadedCount() {
            return getCache<T>().size();
        }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<IResourceCache>> m_caches;

        template<typename T>
        ResourceCache<T> &getCache() {
            auto typeIdx = std::type_index(typeid(T));
            auto it = m_caches.find(typeIdx);
            if (it == m_caches.end())
                throw std::runtime_error("No ResourceCache registered for this type");

            return static_cast<ResourceCache<T> &>(*it->second);
        }
    };

}

#endif //PIXLENGINE_RESOURCEMANAGER_H
