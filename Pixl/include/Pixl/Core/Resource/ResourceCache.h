//
// Created by ChiroYuki on 07/08/2025.
//

#ifndef PIXLENGINE_RESOURCECACHE_H
#define PIXLENGINE_RESOURCECACHE_H

#include "Resource.h"
#include "IResourceLoader.h"

namespace Pixl {

    class IResourceCache {
    public:
        virtual ~IResourceCache() = default;

        virtual void clear() = 0;

        virtual size_t size() const = 0;
    };

    template<typename T>
    class ResourceCache : public IResourceCache {
        static_assert(std::is_base_of_v<Resource, T>, "T must inherit from Resource");

    public:
        explicit ResourceCache(Ref<IResourceLoader<T>> loader) : m_loader(std::move(loader)) {}

        Ref<T> getOrLoad(const std::string &name) {
            if (auto it = m_resources.find(name); it != m_resources.end())
                return it->second;

            if (!m_loader)
                throw std::runtime_error("No loader registered for resource: " + name);

            Ref<T> resource = m_loader->load(name);
            if (!resource)
                throw std::runtime_error("Failed to load resource: " + name);

            m_resources[name] = resource;
            return resource;
        }

        Ref<T> forceReload(const std::string &name) {
            if (!m_loader)
                throw std::runtime_error("No loader registered for resource: " + name);

            auto resource = m_loader->load(name);
            if (!resource)
                throw std::runtime_error("Failed to reload resource: " + name);

            m_resources[name] = resource;
            return resource;
        }

        Ref<T> get(const std::string &name) const {
            if (auto it = m_resources.find(name); it != m_resources.end())
                return it->second;

            return nullptr;
        }

        bool exists(const std::string &name) const {
            return m_resources.find(name) != m_resources.end();
        }

        void unload(const std::string &name) {
            m_resources.erase(name);
        }

        // Interface IResourceCache
        void clear() override { m_resources.clear(); }

        size_t size() const override { return m_resources.size(); }

    private:
        std::unordered_map<std::string, std::shared_ptr<T>> m_resources;
        Ref<IResourceLoader<T>> m_loader;
    };

}

#endif //PIXLENGINE_RESOURCECACHE_H
