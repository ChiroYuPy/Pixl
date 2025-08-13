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

        // === STATS ===
        void printCacheStats() const;
        void cleanupNonPersistent();
        void clear();

    private:
        std::string getAbsolutePath(const std::string &relativePath) const;

        // Texture management
        Ref<TextureLoader> m_textureLoader;
        Scope<ResourceManager<Texture>> m_textureManager;

        // Shader management
        Ref<ShaderLoader> m_shaderLoader;
        Scope<ResourceManager<Shader>> m_shaderManager;

        std::string m_basePath;
    };

}

#endif //PIXLENGINE_RESOURCESERVICE_H
