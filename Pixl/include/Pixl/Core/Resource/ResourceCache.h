//
// Created by ChiroYuki on 07/08/2025.
//

#ifndef PIXLENGINE_RESOURCECACHE_H
#define PIXLENGINE_RESOURCECACHE_H

#include "Resource.h"

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
        using LoaderFunc = std::function<Ref<T>(const std::string &)>;

        explicit ResourceCache(LoaderFunc loader) : loader_(std::move(loader)) {}

        Ref<T> getOrLoad(const std::string &name) {
            if (auto it = resources_.find(name); it != resources_.end())
                return it->second;

            if (!loader_)
                throw std::runtime_error("No loader registered for resource: " + name);

            auto resource = loader_(name);
            if (!resource)
                throw std::runtime_error("Failed to load resource: " + name);

            resources_[name] = resource;
            return resource;
        }

        Ref<T> forceReload(const std::string &name) {
            if (!loader_)
                throw std::runtime_error("No loader registered for resource: " + name);

            auto resource = loader_(name);
            if (!resource)
                throw std::runtime_error("Failed to reload resource: " + name);

            resources_[name] = resource;
            return resource;
        }

        Ref<T> get(const std::string &name) const {
            if (auto it = resources_.find(name); it != resources_.end())
                return it->second;

            return nullptr;
        }

        bool exists(const std::string &name) const {
            return resources_.find(name) != resources_.end();
        }

        void unload(const std::string &name) {
            resources_.erase(name);
        }

        // Interface IResourceCache
        void clear() override { resources_.clear(); }

        size_t size() const override { return resources_.size(); }

    private:
        std::unordered_map<std::string, std::shared_ptr<T>> resources_;
        LoaderFunc loader_;
    };

}

#endif //PIXLENGINE_RESOURCECACHE_H
