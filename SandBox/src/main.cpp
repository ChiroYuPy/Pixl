//
// Created by ChiroYuki on 26/07/2025.
//

#include <iostream>

#include "Pixl/Core/EntryPoint.h"

class SandboxApp : public Pixl::Application {
public:
    explicit SandboxApp(const Pixl::ApplicationSpecification& specification)
            : Pixl::Application(specification) {}

    ~SandboxApp() override = default;
};

Pixl::Application* Pixl::CreateApplication() {
    ApplicationSpecification spec;
    spec.Name = "SandboxApp";
    spec.WorkingDirectory = R"(C:\Users\ChiroYuki\CLionProjects\Pixl\SandBox\resources)";

    return new SandboxApp(spec);
}