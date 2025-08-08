//
// Created by ChiroYuki on 02/08/2025.
//

#include "SandBox.h"

#include "layers/CameraTestLayer.h"
#include "layers/HueExempleLayer.h"
#include "layers/ResourceLoadingTestLayer.h"

#include <iostream>

SandboxApp::SandboxApp(const Pixl::ApplicationSpecification &specification)
        : Pixl::Application(specification) {
    PushLayer(new ResourceLoadingTestLayer());
    PushLayer(new HueExempleLayer());
    PushLayer(new CameraTestLayer());
}

Pixl::Application* Pixl::createApplication() {
    Pixl::ApplicationSpecification spec;
    spec.Name = "SandboxApp";
    spec.workingDirectory = R"(C:\Users\ChiroYuki\CLionProjects\Pixl\SandBox)";

    return new SandboxApp(spec);
}