//
// Created by ChiroYuki on 09/08/2025.
//

#ifndef PIXLENGINE_ENTTTESTLAYER_H
#define PIXLENGINE_ENTTTESTLAYER_H

#include "Pixl/Pixl.h"

#include <entt/entt.hpp>

class EnttTestLayer : public Pixl::Layer {
public:
    void onAttach() override;
    void onDetach() override;
    void onUpdate(Pixl::Time& deltaTime) override;
    void onEvent(Pixl::Event& event) override;
};

#endif //PIXLENGINE_ENTTTESTLAYER_H
