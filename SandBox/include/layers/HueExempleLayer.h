//
// Created by ChiroYuki on 08/08/2025.
//

#ifndef PIXLENGINE_HUEEXEMPLELAYER_H
#define PIXLENGINE_HUEEXEMPLELAYER_H

#include "Pixl/Pixl.h"

class HueExempleLayer : public Pixl::Layer {
public:
    void onAttach() override;
    void onDetach() override;
    void onUpdate(Pixl::Time& dt) override;
    void onEvent(Pixl::Event& e) override;

private:
    float m_Hue = 0.0f;
};

#endif //PIXLENGINE_HUEEXEMPLELAYER_H
