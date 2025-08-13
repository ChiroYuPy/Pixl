//
// Created by ChiroYuki on 07/08/2025.
//

#ifndef PIXLENGINE_RESOURCEMANAGER_H
#define PIXLENGINE_RESOURCEMANAGER_H

#include "Pixl/Core/Resource/Loaders/IResourceLoader.h"
#include "Resource.h"

#include <iostream>
#include <unordered_map>

namespace Pixl {

    template<typename R>
    class ResourceManager {
    public:
        explicit ResourceManager(std::shared_ptr<IResourceLoader<R>> loader)
                : m_loader(std::move(loader)) {}

        ~ResourceManager() = default;

        std::optional<Ref<R>> get(const std::string &absolutePath) {
            std::lock_guard<std::mutex> lock(m_mutex);

            // Nettoyer les entrées expirées
            cleanupExpiredEntries();

            // Chercher dans le cache
            auto it = m_cache.find(absolutePath);
            if (it != m_cache.end()) {
                if (auto ptr = it->second.lock()) {
                    // Incrémenter le compteur de référence
                    ptr->refCount++;
                    return ptr;
                }
                // L'entrée est expirée, la supprimer
                m_cache.erase(it);
            }

            // Charger la ressource
            auto loaded = m_loader->load(absolutePath);
            if (!loaded.has_value()) {
                std::cerr << "Erreur : Impossible de charger la ressource '" << absolutePath << "'\n";
                return std::nullopt;
            }

            // Initialiser les métadonnées de la ressource
            auto resource = *loaded;
            resource->path = absolutePath;
            resource->refCount = 1;

            // Ajouter au cache
            m_cache[absolutePath] = resource;

            return resource;
        }

        // Méthode pour libérer explicitement une référence
        void release(const std::string &absolutePath) {
            std::lock_guard<std::mutex> lock(m_mutex);

            auto it = m_cache.find(absolutePath);
            if (it != m_cache.end()) {
                if (auto ptr = it->second.lock()) {
                    if (ptr->refCount > 0) {
                        ptr->refCount--;
                    }

                    // Si la ressource n'est pas persistante et n'a plus de références,
                    // on peut la marquer pour suppression
                    if (!ptr->persistent && ptr->refCount == 0) {
                        // La ressource sera automatiquement supprimée du cache
                        // lors du prochain nettoyage
                    }
                }
            }
        }

        // Méthode pour marquer une ressource comme persistante
        void makePersistent(const std::string &absolutePath, bool persistent = true) {
            std::lock_guard<std::mutex> lock(m_mutex);

            auto it = m_cache.find(absolutePath);
            if (it != m_cache.end()) {
                if (auto ptr = it->second.lock()) {
                    ptr->persistent = persistent;
                }
            }
        }

        // Obtenir des statistiques sur le cache
        struct CacheStats {
            size_t totalEntries;
            size_t validEntries;
            size_t expiredEntries;
        };

        CacheStats getStats() const {
            std::lock_guard<std::mutex> lock(m_mutex);

            CacheStats stats{};
            stats.totalEntries = m_cache.size();

            for (const auto &pair: m_cache) {
                if (pair.second.expired()) {
                    stats.expiredEntries++;
                } else {
                    stats.validEntries++;
                }
            }

            return stats;
        }

        void clear() {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_cache.clear();
        }

        // Nettoyer uniquement les ressources non persistantes
        void clearNonPersistent() {
            std::lock_guard<std::mutex> lock(m_mutex);

            auto it = m_cache.begin();
            while (it != m_cache.end()) {
                if (auto ptr = it->second.lock()) {
                    if (!ptr->persistent) {
                        it = m_cache.erase(it);
                    } else {
                        ++it;
                    }
                } else {
                    it = m_cache.erase(it);
                }
            }
        }

    private:
        void cleanupExpiredEntries() {
            auto it = m_cache.begin();
            while (it != m_cache.end()) {
                if (it->second.expired()) {
                    it = m_cache.erase(it);
                } else {
                    ++it;
                }
            }
        }

        std::unordered_map<std::string, std::weak_ptr<R>> m_cache;
        Ref<IResourceLoader<R>> m_loader;
        mutable std::mutex m_mutex;
    };
}

#endif //PIXLENGINE_RESOURCEMANAGER_H
