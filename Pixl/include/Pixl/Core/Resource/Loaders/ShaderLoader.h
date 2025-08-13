//
// Created by ChiroYuki on 13/08/2025.
//

#ifndef PIXLENGINE_SHADERLOADER_H
#define PIXLENGINE_SHADERLOADER_H

#include "Pixl/Rendering/Objects/Shader.h"
#include "IResourceLoader.h"

#include <nlohmann/json.hpp>
#include <optional>
#include <string>

namespace Pixl {

    struct ShaderConfig {
        std::string vertex;
        std::string fragment;
        std::string name;
        // Optionnel: defines/macros à injecter
        std::vector<std::string> defines;
    };

    class ShaderLoader : public IResourceLoader<Shader> {
    public:
        explicit ShaderLoader(std::string  basePath);

        std::optional<std::shared_ptr<Shader>> load(const std::string& configPath) override;

    private:
        bool parseConfig(const nlohmann::json& j, ShaderConfig& config);
        std::string processDefines(const std::string& source, const std::vector<std::string>& defines);

        std::string m_basePath;
    };

}

#endif //PIXLENGINE_SHADERLOADER_H
