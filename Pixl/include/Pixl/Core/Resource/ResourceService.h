//
// Created by ChiroYuki on 08/08/2025.
//

#ifndef PIXLENGINE_RESOURCESERVICE_H
#define PIXLENGINE_RESOURCESERVICE_H

#include "Pixl/Core/Base.h"
#include "Pixl/Core/Resource/TextureLoader.h"
#include "Pixl/Core/Resource/ResourceManager.h"

#include <string>
#include <filesystem>

namespace Pixl {

    class ResourceService {
    public:
        ResourceService();

        std::optional<Ref<Texture>> getTexture(const std::string &relativePath);

        void clear();

    private:
        Ref<TextureLoader> m_textureLoader;
        Scope<ResourceManager<Texture>> m_textureManager;
    };

}

#endif //PIXLENGINE_RESOURCESERVICE_H
