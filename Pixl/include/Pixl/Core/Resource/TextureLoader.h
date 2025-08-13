//
// Created by ChiroYuki on 08/08/2025.
//

#ifndef PIXLENGINE_TEXTURELOADER_H
#define PIXLENGINE_TEXTURELOADER_H

#include "IResourceLoader.h"
#include "Pixl/Rendering/Objects/Texture.h"

#include <glad/glad.h>
#include <nlohmann/json.hpp>

#include <optional>

namespace Pixl {

    struct TextureConfig {
        std::string file;
        std::string wrapMode = "clamp";
        std::string filter = "linear";
    };

    enum class WrapMode : GLint {
        Repeat = GL_REPEAT,
        ClampToEdge = GL_CLAMP_TO_EDGE
    };

    enum class FilterMode : GLint {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR
    };

    class TextureLoader : public IResourceLoader<Texture> {
    public:
        explicit TextureLoader(const std::string& basePath);

        std::optional<std::shared_ptr<Texture>> load(const std::string& id) override;

    private:
        bool parseConfig(const nlohmann::json& j, TextureConfig& config);

        static std::optional<WrapMode> parseWrapMode(const std::string& mode);
        static std::optional<FilterMode> parseFilter(const std::string& filter);

        std::string m_basePath;
    };

}

#endif //PIXLENGINE_TEXTURELOADER_H
