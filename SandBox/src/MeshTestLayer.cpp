//
// Created by ChiroYuki on 05/08/2025.
//

#include "../include/MeshTestLayer.h"

void MeshTestLayer::onAttach() {
    Pixl::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
    Pixl::Input::setCursorMode(Pixl::CursorMode::Visible);

    camera = Pixl::makeScope<Pixl::PerspectiveCamera>(
            90.0f, Pixl::Application::get().getWindow().getAspectRatio(), 0.1f, 10000.0f
    );

    camera->setPosition({3.0f, 3.0f, 3.0f});
    camera->lookAt({0.0f, 0.0f, 0.0f});

    cameraController = Pixl::makeScope<Pixl::OrbitController>(camera.get());

    Pixl::Ref<Pixl::CubeGeometry> cubeGeometry = Pixl::makeRef<Pixl::CubeGeometry>();
    Pixl::Ref<Pixl::ColorMaterial> redMaterial = Pixl::makeRef<Pixl::ColorMaterial>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    Pixl::Ref<Pixl::ColorMaterial> greenMaterial = Pixl::makeRef<Pixl::ColorMaterial>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

    Pixl::Ref<Pixl::VertexColorMaterial> colorMaterial = Pixl::makeRef<Pixl::VertexColorMaterial>();

    cubeMesh = Pixl::makeScope<Pixl::MultiMaterialMesh>(cubeGeometry);
    cubeMesh->addSubMesh(redMaterial, 0, 18);
    cubeMesh->addSubMesh(greenMaterial, 18, 18);

    // cubeMesh->addSubMesh(colorMaterial, 0, 36);
}

void MeshTestLayer::onDetach() {

}

void MeshTestLayer::onUpdate(Pixl::Time &deltaTime) {
    Pixl::RenderCommand::Clear();

    Pixl::Renderer::beginFrame(*camera);

    camera->setAspectRatio(Pixl::Application::get().getWindow().getAspectRatio());

    cameraController->update(deltaTime);

    glm::mat4 projMatrix = camera->getProjectionMatrix();
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 viewProj = projMatrix * viewMatrix;

    auto cubeTransform = glm::mat4(1.0f);
    cubeTransform = glm::translate(cubeTransform, glm::vec3(0.0f, 0.0f, 0.0f));

    cubeMesh->render(cubeTransform, viewProj);

    Pixl::Renderer::endFrame();
}

void MeshTestLayer::onEvent(Pixl::Event &event) {
    static bool cameraControlEnabled = false;

    Pixl::EventDispatcher dispatcher(event);

    if (cameraControlEnabled) {
        dispatcher.dispatch<Pixl::MouseMovedEvent>([this](Pixl::MouseMovedEvent& e) {
            return cameraController->onMouseMoved(e);
        });

        dispatcher.dispatch<Pixl::MouseButtonPressedEvent>([this](Pixl::MouseButtonPressedEvent& e) {
            return cameraController->onMousePressed(e);
        });

        dispatcher.dispatch<Pixl::MouseButtonReleasedEvent>([this](Pixl::MouseButtonReleasedEvent& e) {
            return cameraController->onMouseReleased(e);
        });

        dispatcher.dispatch<Pixl::MouseScrolledEvent>([this](Pixl::MouseScrolledEvent& e) {
            return cameraController->onMouseScrolled(e);
        });
    }

    dispatcher.dispatch<Pixl::KeyPressedEvent>([this](Pixl::KeyPressedEvent& e) {
        switch (e.getKeyCode()) {
            case Pixl::Key::Escape:
                if (cameraControlEnabled) {
                    Pixl::Input::setCursorMode(Pixl::CursorMode::Visible);
                    cameraControlEnabled = false;
                    std::cout << "Camera control disabled" << std::endl;
                } else {
                    Pixl::Input::setCursorMode(Pixl::CursorMode::Captured);
                    cameraControlEnabled = true;
                    std::cout << "Camera control enabled - Use mouse to orbit, scroll to zoom, right-click to pan" << std::endl;
                }
                return true;

            case Pixl::Key::R:
                if (cameraController) {
                    camera->setPosition({3.0f, 3.0f, 3.0f});
                    camera->lookAt({0.0f, 0.0f, 0.0f});

                    cameraController->setTarget({0.0f, 0.0f, 0.0f});
                    cameraController->setDistance(glm::length(glm::vec3(3.0f, 3.0f, 3.0f)));
                    cameraController->reset();

                    std::cout << "Camera reset to initial position" << std::endl;
                }
                return true;

            case Pixl::Key::F:
                if (cameraController) {
                    cameraController->setTarget({0.0f, 0.0f, 0.0f});
                    cameraController->setDistance(5.0f);
                    std::cout << "Camera focused on origin" << std::endl;
                }
                return true;
        }
        return false;
    });

    /*
    dispatcher.dispatch<Pixl::WindowResizeEvent>([this](Pixl::WindowResizeEvent& e) {
        cameraController->resetMouse();
        return false;
    });
     */
}
