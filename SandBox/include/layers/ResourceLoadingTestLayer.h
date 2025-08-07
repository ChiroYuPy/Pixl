//
// Created by ChiroYuki on 08/08/2025.
//

#ifndef PIXLENGINE_RESOURCELOADINGTESTLAYER_H
#define PIXLENGINE_RESOURCELOADINGTESTLAYER_H

#include "Pixl/Pixl.h"

class ResourceLoadingTestLayer : public Pixl::Layer {
public:
    void onAttach() override;
    void onDetach() override;
    void onUpdate(Pixl::Time& dt) override;
    void onEvent(Pixl::Event& e) override;
};

#endif //PIXLENGINE_RESOURCELOADINGTESTLAYER_H
