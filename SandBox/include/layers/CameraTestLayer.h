//
// Created by ChiroYuki on 07/08/2025.
//

#ifndef PIXLENGINE_CAMERATESTLAYER_H
#define PIXLENGINE_CAMERATESTLAYER_H

#include "Pixl/Pixl.h"

class CameraTestLayer : public Pixl::Layer {
public:
    void onAttach() override;
    void onDetach() override;
    void onUpdate(Pixl::Time& deltaTime) override;
    void onEvent(Pixl::Event& event) override;

private:
    Pixl::Ref<Pixl::PerspectiveCamera>  camera;
    Pixl::Scope<Pixl::OrbitController>    cameraController;
};

#endif //PIXLENGINE_CAMERATESTLAYER_H
