//
// Created by ChiroYuki on 08/08/2025.
//

#ifndef PIXLENGINE_RESOURCETESTLAYER_H
#define PIXLENGINE_RESOURCETESTLAYER_H

#include "Pixl/Pixl.h"

class ResourceTestLayer : public Pixl::Layer {
public:
    void onAttach() override;
    void onDetach() override;
    void onUpdate(Pixl::Time& dt) override;
    void onEvent(Pixl::Event& e) override;

private:
    void loadTestSet();
    void printStats();
};

#endif //PIXLENGINE_RESOURCETESTLAYER_H
