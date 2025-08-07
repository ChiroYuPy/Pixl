//
// Created by ChiroYuki on 07/08/2025.
//

#ifndef PIXLENGINE_RESOURCEMANAGER_H
#define PIXLENGINE_RESOURCEMANAGER_H

#include "ResourceCache.h"

namespace Pixl {

    class ResourceManager {
    public:
        template<typename T>
        void registerLoader(typename ResourceCache<T>::LoaderFunc loader) {
            auto typeIdx = std::type_index(typeid(T));
            caches_[typeIdx] = std::make_unique<ResourceCache<T>>(std::move(loader));
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
            for (auto &[type, cache]: caches_)
                cache->clear();
        }

        template<typename T>
        void clearType() {
            getCache<T>().clear();
        }

        // Pour les statistiques et le debug
        template<typename T>
        size_t getLoadedCount() {
            return getCache<T>().size();
        }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<IResourceCache>> caches_;

        template<typename T>
        ResourceCache<T> &getCache() {
            auto typeIdx = std::type_index(typeid(T));
            auto it = caches_.find(typeIdx);
            if (it == caches_.end())
                throw std::runtime_error("No ResourceCache registered for this type");

            return static_cast<ResourceCache<T> &>(*it->second);
        }
    };

}

#endif //PIXLENGINE_RESOURCEMANAGER_H
