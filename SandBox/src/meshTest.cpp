//
// Created by ChiroYuki on 02/08/2025.
//

#include <iostream>

#include "Pixl/Pixl.h"
#include "Pixl/Core/EntryPoint.h"

class SandboxApp : public Pixl::Application {
private:
    Pixl::Scope<Pixl::PerspectiveCamera> camera;
    Pixl::Scope<Pixl::FPSController> fpsController;
    Pixl::Scope<Pixl::MultiMaterialMesh> cubeMesh;

public:
    explicit SandboxApp(const Pixl::ApplicationSpecification& specification)
    : Pixl::Application(specification) {
        Pixl::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});

        Pixl::Input::setCursorMode(Pixl::CursorMode::Visible);

        camera = Pixl::makeScope<Pixl::PerspectiveCamera>(
                90.0f, getWindow().getAspectRatio(), 0.1f, 10000.0f
        );

        camera->setPosition({3.0f, 3.0f, 3.0f});
        camera->lookAt({0.0f, 0.0f, 0.0f});

        fpsController = Pixl::makeScope<Pixl::FPSController>(camera.get());

        Pixl::Ref<Pixl::CubeGeometry> cubeGeometry = Pixl::makeRef<Pixl::CubeGeometry>();
        Pixl::Ref<Pixl::ColorMaterial> redMaterial = Pixl::makeRef<Pixl::ColorMaterial>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        Pixl::Ref<Pixl::ColorMaterial> greenMaterial = Pixl::makeRef<Pixl::ColorMaterial>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

        Pixl::Ref<Pixl::VertexColorMaterial> colorMaterial = Pixl::makeRef<Pixl::VertexColorMaterial>();

        cubeMesh = Pixl::makeScope<Pixl::MultiMaterialMesh>(cubeGeometry);
        cubeMesh->addSubMesh(redMaterial, 0, 18);
        cubeMesh->addSubMesh(greenMaterial, 18, 18);

        // cubeMesh->addSubMesh(colorMaterial, 0, 36);
    }

    void onUpdate() override {
        Pixl::RenderCommand::Clear();

        Pixl::Renderer::beginFrame(*camera);

        camera->setAspectRatio(getWindow().getAspectRatio());

        float moveSpeed = 5.0f * 0.017f /* Pixl::Time::deltaTime() */;

        if (Pixl::Input::isKeyPressed(Pixl::Key::W)) {
            camera->moveRelative({0, 0, -moveSpeed});
        }
        if (Pixl::Input::isKeyPressed(Pixl::Key::S)) {
            camera->moveRelative({0, 0, moveSpeed});
        }
        if (Pixl::Input::isKeyPressed(Pixl::Key::A)) {
            camera->moveRelative({-moveSpeed, 0, 0});
        }
        if (Pixl::Input::isKeyPressed(Pixl::Key::D)) {
            camera->moveRelative({moveSpeed, 0, 0});
        }
        if (Pixl::Input::isKeyPressed(Pixl::Key::Space)) {
            camera->move({0, moveSpeed, 0});
        }
        if (Pixl::Input::isKeyPressed(Pixl::Key::LeftShift)) {
            camera->move({0, -moveSpeed, 0});
        }

        glm::mat4 projMatrix = camera->getProjectionMatrix();
        glm::mat4 viewMatrix = camera->getViewMatrix();
        glm::mat4 viewProj = projMatrix * viewMatrix;

        auto cubeTransform = glm::mat4(1.0f);
        cubeTransform = glm::translate(cubeTransform, glm::vec3(0.0f, 0.0f, 0.0f));

        cubeMesh->render(cubeTransform, viewProj);

        Pixl::Renderer::endFrame();
    }

    void onEvent(Pixl::Event& e) {
        Pixl::Application::onEvent(e); // default events

        Pixl::EventDispatcher dispatcher(e);
        dispatcher.dispatch<Pixl::MouseMovedEvent>([this](Pixl::MouseMovedEvent& e) {
            return fpsController->onMouseMoved(e);
        });

        dispatcher.dispatch<Pixl::KeyPressedEvent>([this](Pixl::KeyPressedEvent& e) {
            if (e.getKeyCode() == Pixl::Key::Escape) {
                if (Pixl::Input::getCursorMode() == Pixl::CursorMode::Captured) {
                    Pixl::Input::setCursorMode(Pixl::CursorMode::Visible);
                    fpsController->resetMouse();
                } else {
                    Pixl::Input::setCursorMode(Pixl::CursorMode::Captured);
                }
                return true;
            }
            return false;
        });

        dispatcher.dispatch<Pixl::WindowResizeEvent>([this](Pixl::WindowResizeEvent& e) {
            fpsController->resetMouse();
            return false;
        });
    }

    ~SandboxApp() override = default;
};

Pixl::Application* Pixl::createApplication() {
    Pixl::ApplicationSpecification spec;
    spec.Name = "SandboxApp";
    spec.WorkingDirectory = R"(C:\Users\ChiroYuki\CLionProjects\Pixl\SandBox)";

    return new SandboxApp(spec);
}