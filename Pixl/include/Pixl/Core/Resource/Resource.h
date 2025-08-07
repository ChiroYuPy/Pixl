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

    class Resource {
    public:
        virtual ~Resource() = default;

        virtual void use() const = 0;

        const std::string &getName() const { return name; }

    protected:
        explicit Resource(std::string name) : name(std::move(name)) {}

    private:
        std::string name;
    };

    class Texture : public Resource {
    public:
        explicit Texture(const std::string &name) : Resource(name) {}

        void use() const override {
            std::cout << "Using texture: " << getName() << "\n";
        }
    };

}

#endif //PIXLENGINE_RESOURCE_H
