#pragma once

#include "Pixl/Rendering/Material/Material.h"
#include "Pixl/Core/Resource/Loaders/IResourceLoader.h"

#include <string>
#include <memory>

namespace Pixl {

    class MaterialLoader : public IResourceLoader<Material> {
    public:
        MaterialLoader() = default;
        virtual ~MaterialLoader() override;

        std::optional<Ref<Material>> load(const std::string& path) override;
    };

}
