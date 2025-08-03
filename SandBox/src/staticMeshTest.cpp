//
// Created by ChiroYuki on 02/08/2025.
//

#include <iostream>

#include "Pixl/Pixl.h"
#include "Pixl/Core/EntryPoint.h"

class SandboxApp : public Pixl::Application {
private:
    Pixl::Scope<Pixl::PerspectiveCamera> camera;
    Pixl::Scope<Pixl::StaticMesh> cubeMesh;

public:
    explicit SandboxApp(const Pixl::ApplicationSpecification& specification)
    : Pixl::Application(specification) {
        Pixl::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});

        camera = Pixl::makeScope<Pixl::PerspectiveCamera>(
                90.0f, getWindow().getAspectRatio(), 0.1f, 10000.0f
        );

        camera->setPosition({3.0f, 3.0f, 3.0f});
        camera->lookAt({0.0f, 0.0f, 0.0f});


        Pixl::Ref<Pixl::CubeGeometry> cubeGeometry = Pixl::makeRef<Pixl::CubeGeometry>();

        auto red = glm::vec4(0.5f, 0.1f, 1.0f, 1.0f); // alpha à 1.0f sinon transparent
        Pixl::Ref<Pixl::ColorMaterial> colorMaterial = Pixl::makeRef<Pixl::ColorMaterial>(red);

        cubeMesh = Pixl::makeScope<Pixl::StaticMesh>(cubeGeometry, colorMaterial);
    }

    void onUpdate() override {
        Pixl::RenderCommand::Clear();

        Pixl::Renderer::beginFrame(*camera);

        camera->setAspectRatio(getWindow().getAspectRatio());
        glm::mat4 projMatrix = camera->getProjectionMatrix();
        glm::mat4 viewMatrix = camera->getViewMatrix();
        glm::mat4 viewProj = projMatrix * viewMatrix;

        auto cubeTransform = glm::mat4(1.0f);

        cubeTransform = glm::translate(cubeTransform, glm::vec3(0.0f, 0.0f, 0.0f));

        cubeMesh->render(cubeTransform, viewProj);

        Pixl::Renderer::endFrame();
    }

    ~SandboxApp() override = default;
};

Pixl::Application* Pixl::createApplication() {
    Pixl::ApplicationSpecification spec;
    spec.Name = "SandboxApp";
    spec.WorkingDirectory = R"(C:\Users\ChiroYuki\CLionProjects\Pixl\SandBox\resources)"; // chemin ressources

    return new SandboxApp(spec);
}