//
// Created by ChiroYuki on 04/08/2025.
//

#include "Pixl/Core/Layer/Layer.h"

#include <utility>

namespace Pixl {

    Pixl::Layer::Layer(std::string name) : m_name(std::move(name)) {

    }

    const std::string &Layer::getName() const {
        return m_name;
    }

}