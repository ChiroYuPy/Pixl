//
// Created by ChiroYuki on 02/08/2025.
//

#include <iostream>

#include "Pixl/Pixl.h"
#include "Pixl/Core/EntryPoint.h"

class SandboxApp : public Pixl::Application {
private:
    Pixl::Scope<Pixl::PerspectiveCamera> camera;

    Pixl::Scope<Pixl::Mesh> cubeMesh;

public:
    explicit SandboxApp(const Pixl::ApplicationSpecification& specification)
    : Pixl::Application(specification) {
        Pixl::RenderCommand::SetClearColor({0, 1, 0, 1});

        camera = Pixl::MakeScope<Pixl::PerspectiveCamera>(
                90.f, GetWindow().GetAspectRatio(), 0.1f, 1000.0f
        );

        Pixl::Ref<Pixl::CubeGeometry> cubeGeometry = Pixl::MakeRef<Pixl::CubeGeometry>();
        auto red = glm::vec4(1, 0, 0, 0);
        Pixl::Ref<Pixl::ColorMaterial> colorMaterial = Pixl::MakeRef<Pixl::ColorMaterial>(red);
        cubeMesh = Pixl::MakeScope<Pixl::Mesh>(cubeGeometry, colorMaterial);
    }

    void OnUpdate() override {
        Pixl::RenderCommand::Clear();

        Pixl::Renderer::beginFrame(*camera);

        camera->setAspectRatio(GetWindow().GetAspectRatio());
        glm::mat4 projMatrix = camera->getProjectionMatrix();
        glm::mat4 viewMatrix = camera->getViewMatrix();
        glm::mat4 viewProj = projMatrix * viewMatrix;

        auto cubeTransform = glm::mat4(1.0f);
        cubeMesh->render(cubeTransform);


        Pixl::Renderer::endFrame();
    }

    ~SandboxApp() override = default;
};

Pixl::Application* Pixl::CreateApplication() {
    ApplicationSpecification spec;
    spec.Name = "SandboxApp";
    spec.WorkingDirectory = R"(C:\Users\ChiroYuki\CLionProjects\Pixl\SandBox\resources)"; // set your resources folder

    return new SandboxApp(spec);
}