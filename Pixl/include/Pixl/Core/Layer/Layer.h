//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_LAYER_H
#define PIXLENGINE_LAYER_H

#include "Pixl/Core/Base.h"
#include "Pixl/Core/Time/Time.h"
#include "Pixl/Events/Event.h"

#include <string>

namespace Pixl {

    class Layer {
    public:
        Layer(std::string  name = "Layer");
        virtual ~Layer() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(Time& ts) {}
        virtual void onEvent(Event& event) {}

        const std::string& getName() const;
    protected:
        std::string m_name;
    };

}

#endif //PIXLENGINE_LAYER_H
