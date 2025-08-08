//
// Created by ChiroYuki on 07/08/2025.
//

#include "layers/CameraTestLayer.h"

void CameraTestLayer::onAttach() {
    Pixl::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});

    // camera & cameraController setup
    float ar = Pixl::Application::get().getWindow().getAspectRatio();
    camera = Pixl::MakeScope<Pixl::PerspectiveCamera>(90.f, ar, 0.1f, 10000.f);
    camera->setPosition({3, 3, 3});

    cameraController = Pixl::MakeScope<Pixl::OrbitController>(camera.get());
    cameraController->setOrientation(135, 45);

    // Cube & material setup
    auto geo = Pixl::Geometry::createCube();
    auto mat = Pixl::MaterialFactory::createFromSource( CUBE_VERT, CUBE_FRAG);
    mat->setProperty("u_color", glm::vec4(0.8f,0.2f,0.4f,1.f));
    mesh = Pixl::MakeScope<Pixl::Mesh>(geo, mat);
}

void CameraTestLayer::onDetach() {

}

void CameraTestLayer::onUpdate(Pixl::Time &dt) {
    Pixl::RenderCommand::Clear();

    Pixl::Renderer::beginFrame(*camera);

    cameraController->update(dt);

    glm::mat4 projMatrix = camera->getProjectionMatrix();
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 viewProj = projMatrix * viewMatrix;

    auto cubeTransform = glm::mat4(1.0f);
    cubeTransform = glm::translate(cubeTransform, glm::vec3(0.0f, 0.0f, 0.0f));
    mesh->setTransform(cubeTransform);

    mesh->render(viewProj);

    Pixl::Renderer::endFrame();
}

void CameraTestLayer::onEvent(Pixl::Event &event) {
    static bool cameraControlEnabled = false;

    Pixl::EventDispatcher dispatcher(event);

    // --- Mouse input ---
    dispatcher.dispatch<Pixl::MouseButtonPressedEvent>([&](Pixl::MouseButtonPressedEvent& e) {
        if (e.getMouseButton() == Pixl::Mouse::Left && !cameraControlEnabled) {
            Pixl::Input::setCursorMode(Pixl::CursorMode::Captured);
            cameraControlEnabled = true;

            if (cameraController)
                cameraController->resetMouse();

            std::cout << "Camera control enabled - Use mouse to orbit, scroll to zoom, right-click to pan" << std::endl;
            return true;
        }
        return false;
    });

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

    // --- Keyboard input ---
    dispatcher.dispatch<Pixl::KeyPressedEvent>([&](Pixl::KeyPressedEvent& e) {
        switch (e.getKeyCode()) {
            case Pixl::Key::Escape:
                if (cameraControlEnabled) {
                    Pixl::Input::setCursorMode(Pixl::CursorMode::Visible);
                    cameraControlEnabled = false;
                    std::cout << "Camera control disabled" << std::endl;
                } else {
                    Pixl::Application::get().close(); // Quitter l'application si non en mode contrôle
                }
                return true;

            case Pixl::Key::F3:
                static bool localToggle = true;
                if (localToggle)
                    Pixl::RenderCommand::SetPolygonMode(Pixl::PolygonMode::Line);
                else
                    Pixl::RenderCommand::SetPolygonMode(Pixl::PolygonMode::Fill);
                localToggle = !localToggle;
                return true;

            case Pixl::Key::R:
                if (cameraController) {
                    cameraController->reset();

                    cameraController->setDistance(glm::length(glm::vec3(3.0f, 3.0f, 3.0f)));
                    cameraController->setOrientation(135, 45);

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

    dispatcher.dispatch<Pixl::WindowResizeEvent>([this](Pixl::WindowResizeEvent& e) {
        camera->setAspectRatio(Pixl::Application::get().getWindow().getAspectRatio());
        return false;
    });
}