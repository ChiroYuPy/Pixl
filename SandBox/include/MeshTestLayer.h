//
// Created by ChiroYuki on 05/08/2025.
//

#ifndef PIXLENGINE_MESHTESTLAYER_H
#define PIXLENGINE_MESHTESTLAYER_H

#include "Pixl/Pixl.h"

class MeshTestLayer : public Pixl::Layer {
public:
    MeshTestLayer() = default;
    ~MeshTestLayer() override = default;

    void onAttach() override;
    void onDetach() override;

    void onUpdate(Pixl::Time& deltaTime) override;
    void onEvent(Pixl::Event& event) override;

private:
    Pixl::Scope<Pixl::ICamera> camera;
    Pixl::Scope<Pixl::OrbitController> cameraController;
    Pixl::Scope<Pixl::MultiMaterialMesh> cubeMesh;
};

#endif //PIXLENGINE_MESHTESTLAYER_H
