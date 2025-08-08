//
// Created by ChiroYuki on 07/08/2025.
//

#ifndef PIXLENGINE_RESOURCE_H
#define PIXLENGINE_RESOURCE_H

#include "Pixl/Core/Base.h"

#include <string>
#include <utility>
#include <iostream>
#include <functional>
#include <typeindex>

namespace Pixl {

    // Classe de base simple pour toutes les ressources
    class Resource {
    public:
        virtual ~Resource() = default;

        virtual void use() const {}
    };

    // Exemple de ressource texture
    class Texture : public Resource {
    public:
        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }
        const std::vector<uint8_t>& getData() const { return m_data; }

    private:
        friend class TextureLoader; // seul TextureLoader peut modifier ces membres

        void setSize(int w, int h) { m_width = w; m_height = h; }
        void setData(std::vector<uint8_t>&& data) { m_data = std::move(data); }

        int m_width = 0;
        int m_height = 0;
        std::vector<uint8_t> m_data; // pixels RGBA8 par exemple

        // Optionnel: paramètres de wrapping/filter
        int m_wrapMode = 0;
        int m_filter = 0;

        void setWrapMode(int mode) { m_wrapMode = mode; }
        void setFilter(int filter) { m_filter = filter; }
    };

}

#endif //PIXLENGINE_RESOURCE_H
