#include "Pixl/Core/Application.h"
#include "Pixl/Core/Resource/Loaders/MaterialLoader.h"
#include "Pixl/Core/Resource/ResourceManager.h"
#include "Pixl/Rendering/Objects/Shader.h"
#include "Pixl/Rendering/Objects/Texture.h"
#include <nlohmann/json.hpp>
#include <fstream>

namespace Pixl {
    MaterialLoader::~MaterialLoader() = default;

    std::optional<Ref<Material>> MaterialLoader::load(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) return std::nullopt;
        // Vérifier si le fichier est vide
        file.seekg(0, std::ios::end);
        if (file.tellg() == 0) {
            file.close();
            return std::nullopt;
        }
        file.seekg(0, std::ios::beg);
        nlohmann::json j;
        file >> j;
        file.close();

        auto& resourceService = Application::get().getResourceService();
        // Charger le shader
        std::string shaderName = j["shader"];
        auto shaderOpt = resourceService.getShader(shaderName);
        if (!shaderOpt.has_value()) return std::nullopt;
        auto material = std::make_shared<Material>(shaderOpt.value());

        // Charger les textures
        if (j.contains("textures")) {
            for (auto& [name, texPath] : j["textures"].items()) {
                auto textureOpt = resourceService.getTexture(texPath);
                if (textureOpt.has_value()) material->setTexture(name, textureOpt.value());
            }
        }
        // Charger les floats
        if (j.contains("floats")) {
            for (auto& [name, value] : j["floats"].items()) {
                material->setFloat(name, value);
            }
        }
        // Charger les vec3s
        if (j.contains("vec3s")) {
            for (auto& [name, arr] : j["vec3s"].items()) {
                material->setFloat3(name, glm::vec3(arr[0], arr[1], arr[2]));
            }
        }
        // Autres types à ajouter si besoin
        return material;
    }
}
