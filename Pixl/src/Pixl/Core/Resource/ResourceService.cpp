//
// Created by ChiroYuki on 08/08/2025.
//

#include "Pixl/Core/Resource/ResourceService.h"
#include "Pixl/Core/Application.h"

namespace Pixl {

    ResourceService::ResourceService() {
        std::filesystem::path m_basePath = Application::get().getSpecification().workingDirectory;
        m_basePath /= "resources";

        try {
            if (!std::filesystem::exists(m_basePath)) {
                if (std::filesystem::create_directories(m_basePath))
                    std::cout << "[ResourceService] Dossier 'resources' créé : " << m_basePath << std::endl;
                else
                    std::cerr << "[ResourceService] Impossible de créer le dossier 'resources' : " << m_basePath << std::endl;
            }
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "[ResourceService] Erreur filesystem : " << e.what() << std::endl;
        }

        m_textureLoader = MakeRef<TextureLoader>(m_basePath.string());
        m_textureManager = MakeScope<ResourceManager<Texture>>(m_textureLoader);
    }

    std::optional<Ref<Texture>> ResourceService::getTexture(const std::string &relativePath) {
        return m_textureManager->get(relativePath);
    }

    void ResourceService::clear() {
        m_textureManager->clear();
    }

}