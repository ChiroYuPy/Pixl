//
// Created by ChiroYuki on 08/08/2025.
//

#ifndef PIXLENGINE_RESOURCESERVICE_H
#define PIXLENGINE_RESOURCESERVICE_H

#include "Pixl/Core/Base.h"
#include "Pixl/Core/Resource/Loaders/TextureLoader.h"
#include "Pixl/Core/Resource/ResourceManager.h"
#include "Pixl/Rendering/Objects/Texture.h"
#include "Pixl/Core/Resource/Loaders/ShaderLoader.h"
#include "Pixl/Core/Resource/Loaders/MaterialLoader.h"
#include "Pixl/Rendering/Material/Material.h"

#include <string>
#include <filesystem>

namespace Pixl {

    class ResourceService {
    public:
        ResourceService();

        // === TEXTURES ===
        std::optional<Ref<Texture>> getTexture(const std::string &relativePath);
        void releaseTexture(const std::string &relativePath);
        void makeTexturePersistent(const std::string &relativePath, bool persistent = true);
        bool preloadTexture(const std::string &relativePath, bool makePersistent = false);

        // === SHADERS ===
        std::optional<Ref<Shader>> getShader(const std::string &relativePath);
        void releaseShader(const std::string &relativePath);
        void makeShaderPersistent(const std::string &relativePath, bool persistent = true);
        bool preloadShader(const std::string &relativePath, bool makePersistent = false);

        // === MATERIALS ===
        std::optional<Ref<Material>> getMaterial(const std::string &relativePath);
        void releaseMaterial(const std::string &relativePath);
        void makeMaterialPersistent(const std::string &relativePath, bool persistent = true);
        bool preloadMaterial(const std::string &relativePath, bool makePersistent = false);

        // === STATS ===
        void printCacheStats() const;
        void cleanupNonPersistent();
        void clear();

    private:
        std::string getAbsolutePath(const std::string &relativePath) const;

        // Texture management
        std::shared_ptr<TextureLoader> m_textureLoader;
        std::unique_ptr<ResourceManager<Texture>> m_textureManager;

        // Shader management
        std::shared_ptr<ShaderLoader> m_shaderLoader;
        std::unique_ptr<ResourceManager<Shader>> m_shaderManager;

        // Material management
        std::shared_ptr<MaterialLoader> m_materialLoader;
        std::unique_ptr<ResourceManager<Material>> m_materialManager;

        std::string m_basePath;
    };

}

#endif //PIXLENGINE_RESOURCESERVICE_H
