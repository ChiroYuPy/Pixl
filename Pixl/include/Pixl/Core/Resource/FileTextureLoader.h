//
// Created by ChiroYuki on 07/08/2025.
//

#ifndef PIXLENGINE_FILETEXTURELOADER_H
#define PIXLENGINE_FILETEXTURELOADER_H

#include "Resource.h"
#include "IResourceLoader.h"

namespace Pixl {

    class FileTextureLoader : public IResourceLoader<Texture> {
    public:
        Ref<Texture> load(const std::string& logicalPath) override;
    };

}

#endif //PIXLENGINE_FILETEXTURELOADER_H
