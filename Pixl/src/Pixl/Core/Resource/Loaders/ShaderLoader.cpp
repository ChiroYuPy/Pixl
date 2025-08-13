//
// Created by ChiroYuki on 13/08/2025.
//

#include "Pixl/Core/Resource/Loaders/ShaderLoader.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <utility>

namespace Pixl {

    ShaderLoader::ShaderLoader(std::string basePath)
    : m_basePath(std::move(basePath)) {}

    std::optional<std::shared_ptr<Shader>> ShaderLoader::load(const std::string& configPath) {
        // Construire le chemin complet vers le fichier de config JSON
        std::filesystem::path fullConfigPath = std::filesystem::path(m_basePath) / configPath;

        std::ifstream file(fullConfigPath);
        if (!file.is_open()) {
            std::cerr << "Erreur ouverture fichier config shader : " << fullConfigPath << std::endl;
            return std::nullopt;
        }

        nlohmann::json j;
        try {
            file >> j;
        } catch (const nlohmann::json::parse_error& e) {
            std::cerr << "Erreur parsing JSON dans " << fullConfigPath << ": " << e.what() << std::endl;
            return std::nullopt;
        }

        ShaderConfig config;
        if (!parseConfig(j, config)) {
            std::cerr << "Erreur parsing config shader\n";
            return std::nullopt;
        }

        // Construire les chemins complets vers les fichiers de shader
        std::filesystem::path vertexPath = std::filesystem::path(m_basePath) / config.vertex;
        std::filesystem::path fragmentPath = std::filesystem::path(m_basePath) / config.fragment;

        if (!std::filesystem::exists(vertexPath)) {
            std::cerr << "Fichier vertex shader non trouvé : " << vertexPath << std::endl;
            return std::nullopt;
        }

        if (!std::filesystem::exists(fragmentPath)) {
            std::cerr << "Fichier fragment shader non trouvé : " << fragmentPath << std::endl;
            return std::nullopt;
        }

        // Lire les fichiers de shader
        std::ifstream vertexFile(vertexPath);
        std::ifstream fragmentFile(fragmentPath);

        if (!vertexFile || !fragmentFile) {
            std::cerr << "Erreur ouverture des fichiers shader : "
                      << vertexPath << " ou " << fragmentPath << std::endl;
            return std::nullopt;
        }

        std::stringstream vertexBuffer, fragmentBuffer;
        vertexBuffer << vertexFile.rdbuf();
        fragmentBuffer << fragmentFile.rdbuf();

        std::string vertexSource = vertexBuffer.str();
        std::string fragmentSource = fragmentBuffer.str();

        // Traiter les defines si nécessaire
        if (!config.defines.empty()) {
            vertexSource = processDefines(vertexSource, config.defines);
            fragmentSource = processDefines(fragmentSource, config.defines);
        }

        // Créer et charger le shader
        auto shader = std::make_shared<Shader>();
        if (!shader->loadFromSource(vertexSource, fragmentSource)) {
            std::cerr << "Erreur chargement shader : " << configPath << std::endl;
            return std::nullopt;
        }

        return shader;
    }

    bool ShaderLoader::parseConfig(const nlohmann::json& j, ShaderConfig& config) {
        // Vérifier les champs obligatoires
        if (!j.contains("vertex") || !j["vertex"].is_string()) {
            std::cerr << "Config shader invalide : champ 'vertex' manquant ou invalide\n";
            return false;
        }

        if (!j.contains("fragment") || !j["fragment"].is_string()) {
            std::cerr << "Config shader invalide : champ 'fragment' manquant ou invalide\n";
            return false;
        }

        config.vertex = j["vertex"].get<std::string>();
        config.fragment = j["fragment"].get<std::string>();

        // Champs optionnels
        if (j.contains("name") && j["name"].is_string()) {
            config.name = j["name"].get<std::string>();
        }

        if (j.contains("defines") && j["defines"].is_array()) {
            for (const auto& define : j["defines"]) {
                if (define.is_string()) {
                    config.defines.push_back(define.get<std::string>());
                }
            }
        }

        return true;
    }

    std::string ShaderLoader::processDefines(const std::string& source, const std::vector<std::string>& defines) {
        if (defines.empty()) return source;

        std::stringstream result;

        // Ajouter la version en premier (généralement #version XXX)
        std::istringstream sourceStream(source);
        std::string line;
        bool versionFound = false;

        while (std::getline(sourceStream, line)) {
            result << line << "\n";

            // Après la ligne #version, ajouter nos defines
            if (!versionFound && line.find("#version") == 0) {
                versionFound = true;
                for (const auto& define : defines) {
                    result << "#define " << define << "\n";
                }
            }

            // Si pas de #version trouvée et qu'on arrive à une ligne non-commentaire/non-vide
            if (!versionFound && !line.empty() && line[0] != '/' && line.find("#version") != 0) {
                // Ajouter les defines avant cette ligne
                std::string currentLine = result.str();
                result.str("");
                result.clear();

                // Récrire sans la dernière ligne
                size_t lastNewline = currentLine.find_last_of('\n', currentLine.length() - 2);
                if (lastNewline != std::string::npos) {
                    result << currentLine.substr(0, lastNewline + 1);
                }

                // Ajouter les defines
                for (const auto& define : defines) {
                    result << "#define " << define << "\n";
                }

                // Ajouter la ligne courante
                result << line << "\n";
                versionFound = true;
            }
        }

        // Si on n'a jamais trouvé d'endroit pour insérer les defines, les ajouter au début
        if (!versionFound) {
            std::string finalSource;
            for (const auto& define : defines) {
                finalSource += "#define " + define + "\n";
            }
            finalSource += source;
            return finalSource;
        }

        return result.str();
    }

}