//
// Created by ChiroYuki on 07/08/2025.
//

#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

namespace Pixl {

    /*
    struct SamplerDesc {
        std::string wrapS = "repeat";
        std::string wrapT = "repeat";
        std::string minFilter = "linear";
        std::string magFilter = "linear";
        float anisotropy = 0.f;
    };

    struct TextureDesc {
        std::string sourceFile;
        SamplerDesc sampler;
        bool generateMips = true;
    };

    bool LoadTextureDesc(const std::string& jsonPath, TextureDesc& out) {
        std::ifstream file(jsonPath);
        if (!file) return false;

        nlohmann::json j;
        file >> j;

        out.sourceFile   = j.value("source", "");
        out.generateMips = j.value("generateMips", true);

        if (j.contains("sampler")) {
            const auto& s = j["sampler"];
            out.sampler.wrapS     = s.value("wrapS", "repeat");
            out.sampler.wrapT     = s.value("wrapT", "repeat");
            out.sampler.minFilter = s.value("minFilter", "linear");
            out.sampler.magFilter = s.value("magFilter", "linear");
            out.sampler.anisotropy = s.value("anisotropy", 0.f);
        }
        return true;
    }

    ResourceLoader<Texture> CreateFileTextureLoader() {
        return [](const std::string& logicalPath) -> Ref<Texture> {
            namespace fs = std::filesystem;

            fs::path jsonPath = logicalPath;
            if (jsonPath.extension() != ".texture") {
                jsonPath.replace_extension(".texture");
            }
            if (!fs::exists(jsonPath)) {
                std::cerr << "Texture descriptor not found: " << jsonPath << "\n";
                return nullptr;
            }

            TextureDesc desc;
            if (!LoadTextureDesc(jsonPath.string(), desc))
                return nullptr;

            auto texture = MakeRef<Texture>(jsonPath.stem().string());
            // TODO: texture->upload(...);

            return texture;
        };
    }
     */

}