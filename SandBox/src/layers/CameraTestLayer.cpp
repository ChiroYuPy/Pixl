//
// Created by ChiroYuki on 07/08/2025.
//

#include "layers/CameraTestLayer.h"

void CameraTestLayer::onAttach() {
    float ar = Pixl::Application::get().getWindow().getAspectRatio();
    camera = Pixl::MakeScope<Pixl::PerspectiveCamera>(90.f, ar, 0.1f, 10000.f);
    camera->setPosition({12,12,12});
    camera->lookAt({0,0,0});
    cameraController = Pixl::MakeScope<Pixl::OrbitController>(camera.get());

    // Cube + matériau ultra-simple
    auto geo = Pixl::Geometry::createCube();
    auto mat = Pixl::MaterialFactory::createFromSource( CUBE_VERT, CUBE_FRAG);
    mat->setProperty("u_color", glm::vec4(0.8f,0.2f,0.4f,1.f));
    mesh = Pixl::MakeScope<Pixl::Mesh>(geo, mat);
}

void CameraTestLayer::onDetach() {

}

void CameraTestLayer::onUpdate(Pixl::Time &dt) {

}

void CameraTestLayer::onEvent(Pixl::Event &e) {

}