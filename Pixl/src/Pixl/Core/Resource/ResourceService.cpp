//
// Created by ChiroYuki on 08/08/2025.
//

#include "Pixl/Core/Resource/ResourceService.h"
#include "Pixl/Core/Application.h"

namespace Pixl {

    ResourceService::ResourceService()
    : m_basePath("assets/")
    {
        // Init loaders
        m_textureLoader = std::make_shared<TextureLoader>(m_basePath);
        m_shaderLoader = std::make_shared<ShaderLoader>(m_basePath);

        // Init managers
        m_textureManager = std::make_unique<ResourceManager<Texture>>(m_textureLoader);
        m_shaderManager = std::make_unique<ResourceManager<Shader>>(m_shaderLoader);
    }

    // === TEXTURE METHODS ===

    std::optional<Ref<Texture>> ResourceService::getTexture(const std::string &relativePath) {
        std::string absolutePath = getAbsolutePath(relativePath);
        return m_textureManager->get(absolutePath);
    }

    void ResourceService::releaseTexture(const std::string &relativePath) {
        std::string absolutePath = getAbsolutePath(relativePath);
        m_textureManager->release(absolutePath);
    }

    void ResourceService::makeTexturePersistent(const std::string &relativePath, bool persistent) {
        std::string absolutePath = getAbsolutePath(relativePath);
        m_textureManager->makePersistent(absolutePath, persistent);
    }

    bool ResourceService::preloadTexture(const std::string &relativePath, bool makePersistent) {
        auto texture = getTexture(relativePath);
        if (texture.has_value()) {
            if (makePersistent) {
                makeTexturePersistent(relativePath, true);
            }
            return true;
        }
        return false;
    }

    // === SHADER METHODS ===

    std::optional<Ref<Shader>> ResourceService::getShader(const std::string &relativePath) {
        std::string absolutePath = getAbsolutePath(relativePath);
        return m_shaderManager->get(absolutePath);
    }

    void ResourceService::releaseShader(const std::string &relativePath) {
        std::string absolutePath = getAbsolutePath(relativePath);
        m_shaderManager->release(absolutePath);
    }

    void ResourceService::makeShaderPersistent(const std::string &relativePath, bool persistent) {
        std::string absolutePath = getAbsolutePath(relativePath);
        m_shaderManager->makePersistent(absolutePath, persistent);
    }

    bool ResourceService::preloadShader(const std::string &relativePath, bool makePersistent) {
        auto shader = getShader(relativePath);
        if (shader.has_value()) {
            if (makePersistent) {
                makeShaderPersistent(relativePath, true);
            }
            return true;
        }
        return false;
    }

    // === UTILITY METHODS ===

    void ResourceService::printCacheStats() const {
        auto textureStats = m_textureManager->getStats();
        auto shaderStats = m_shaderManager->getStats();

        std::cout << "=== Resource Cache Statistics ===" << std::endl;
        std::cout << "TEXTURES:" << std::endl;
        std::cout << "  Total entries: " << textureStats.totalEntries << std::endl;
        std::cout << "  Valid entries: " << textureStats.validEntries << std::endl;
        std::cout << "  Expired entries: " << textureStats.expiredEntries << std::endl;
        std::cout << "SHADERS:" << std::endl;
        std::cout << "  Total entries: " << shaderStats.totalEntries << std::endl;
        std::cout << "  Valid entries: " << shaderStats.validEntries << std::endl;
        std::cout << "  Expired entries: " << shaderStats.expiredEntries << std::endl;
        std::cout << "==================================" << std::endl;
    }

    void ResourceService::cleanupNonPersistent() {
        m_textureManager->clearNonPersistent();
        m_shaderManager->clearNonPersistent();
    }

    void ResourceService::clear() {
        m_textureManager->clear();
        m_shaderManager->clear();
    }

    std::string ResourceService::getAbsolutePath(const std::string &relativePath) const {
        return std::filesystem::absolute(std::filesystem::path(m_basePath) / relativePath).string();
    }

}