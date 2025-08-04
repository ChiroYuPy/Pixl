//
// Created by ChiroYuki on 04/08/2025.
//

#ifndef PIXLENGINE_LAYER_H
#define PIXLENGINE_LAYER_H


#include <string>
#include "Pixl/Events/Event.h"
#include "Pixl/Core/Time/Time.h"

namespace Pixl {

    class Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Time ts) {}
        virtual void OnEvent(Event& event) {}

        const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };

}

#endif //PIXLENGINE_LAYER_H
