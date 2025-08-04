//
// Created by ChiroYuki on 02/08/2025.
//

#include <iostream>

#include "Pixl/Pixl.h"
#include "Pixl/Core/EntryPoint.h"
#include "Pixl/Core/Time/Time.h"
#include "../include/MeshTestLayer.h"

class SandboxApp : public Pixl::Application {
public:
    explicit SandboxApp(const Pixl::ApplicationSpecification& specification)
    : Pixl::Application(specification) {
        PushLayer(new MeshTestLayer());
    }

    ~SandboxApp() override = default;
};

Pixl::Application* Pixl::createApplication() {
    Pixl::ApplicationSpecification spec;
    spec.Name = "SandboxApp";
    spec.workingDirectory = R"(C:\Users\ChiroYuki\CLionProjects\Pixl\SandBox)";

    return new SandboxApp(spec);
}