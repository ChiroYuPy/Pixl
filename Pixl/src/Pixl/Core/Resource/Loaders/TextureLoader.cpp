//
// Created by ChiroYuki on 08/08/2025.
//

#include "Pixl/Core/Resource/Loaders/TextureLoader.h"

#include <fstream>
#include <iostream>
#include <filesystem>

namespace Pixl {

    TextureLoader::TextureLoader(const std::string &basePath)
    : m_basePath(basePath) {}

    std::optional<std::shared_ptr<Texture>> TextureLoader::load(const std::string& configPath) {
        // Construire le chemin complet vers le fichier de config JSON
        std::filesystem::path fullConfigPath = std::filesystem::path(m_basePath) / configPath;

        std::ifstream file(fullConfigPath);
        if (!file.is_open()) {
            std::cerr << "Erreur ouverture fichier config texture : " << fullConfigPath << std::endl;
            return std::nullopt;
        }

        nlohmann::json j;
        try {
            file >> j;
        } catch (const nlohmann::json::parse_error& e) {
            std::cerr << "Erreur parsing JSON dans " << fullConfigPath << ": " << e.what() << std::endl;
            return std::nullopt;
        }

        TextureConfig config;
        if (!parseConfig(j, config)) {
            std::cerr << "Erreur parsing config texture\n";
            return std::nullopt;
        }

        // Construire le chemin complet vers le fichier de texture à partir du basePath
        std::filesystem::path textureFullPath = std::filesystem::path(m_basePath) / config.file;

        if (!std::filesystem::exists(textureFullPath)) {
            std::cerr << "Fichier texture non trouvé : " << textureFullPath << std::endl;
            return std::nullopt;
        }

        auto texture = std::make_shared<Texture>();
        /*
        if (!texture->loadFromFile(textureFullPath.string())) {
            std::cerr << "Erreur chargement texture : " << textureFullPath << std::endl;
            return std::nullopt;
        }

         auto wrapModeOpt = TextureLoader::parseWrapMode(config.wrapMode);
        if (wrapModeOpt)
            texture->setWrapMode(static_cast<GLint>(*wrapModeOpt));
        else
            texture->setWrapMode(GL_CLAMP_TO_EDGE); // fallback

        auto filterOpt = TextureLoader::parseFilter(config.filter);
        if (filterOpt)
            texture->setFilter(static_cast<GLint>(*filterOpt));
        else
            texture->setFilter(GL_LINEAR); // fallback
        */

        return texture;
    }

    bool TextureLoader::parseConfig(const nlohmann::json& j, TextureConfig& config) {
        if (!j.contains("file") || !j["file"].is_string()) {
            std::cerr << "Config texture invalide : champ 'file' manquant ou invalide\n";
            return false;
        }
        config.file = j["file"].get<std::string>();

        if (j.contains("wrap_mode") && j["wrap_mode"].is_string())
            config.wrapMode = j["wrap_mode"].get<std::string>();

        if (j.contains("filter") && j["filter"].is_string())
            config.filter = j["filter"].get<std::string>();

        return true;
    }

    std::optional<WrapMode> TextureLoader::parseWrapMode(const std::string &mode) {
        if (mode == "repeat") return WrapMode::Repeat;
        if (mode == "clamp") return WrapMode::ClampToEdge;
        return std::nullopt;
    }

    std::optional<FilterMode> TextureLoader::parseFilter(const std::string &filter) {
        if (filter == "nearest") return FilterMode::Nearest;
        if (filter == "linear") return FilterMode::Linear;
        return std::nullopt;
    }

}