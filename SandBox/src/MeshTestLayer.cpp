//
// Created by ChiroYuki on 05/08/2025.
//

#include "../include/MeshTestLayer.h"

MeshTestLayer::MeshTestLayer() {

}

void MeshTestLayer::onAttach() {
    Pixl::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
    Pixl::Input::setCursorMode(Pixl::CursorMode::Visible);

    camera = Pixl::makeScope<Pixl::PerspectiveCamera>(
            90.0f, Pixl::Application::get().getWindow().getAspectRatio(), 0.1f, 10000.0f
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

void MeshTestLayer::onDetach() {

}

void MeshTestLayer::onUpdate(Pixl::Time &deltaTime) {
    Pixl::RenderCommand::Clear();

    Pixl::Renderer::beginFrame(*camera);

    camera->setAspectRatio(Pixl::Application::get().getWindow().getAspectRatio());

    float moveSpeed = 5.0f * deltaTime.asSeconds();

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

void MeshTestLayer::onEvent(Pixl::Event &event) {
    static bool active = false;

    Pixl::EventDispatcher dispatcher(event);

    if (active)
        dispatcher.dispatch<Pixl::MouseMovedEvent>([this](Pixl::MouseMovedEvent& e) {
            return fpsController->onMouseMoved(e);
        });

    dispatcher.dispatch<Pixl::KeyPressedEvent>([](Pixl::KeyPressedEvent& e) {
        if (e.getKeyCode() == Pixl::Key::Escape) {
            if (Pixl::Input::getCursorMode() == Pixl::CursorMode::Captured) {
                Pixl::Input::setCursorMode(Pixl::CursorMode::Visible);
                active = false;
                // fpsController->resetMouse();
            } else {
                Pixl::Input::setCursorMode(Pixl::CursorMode::Captured);
                active = true;
            }
            return true;
        }
        return false;
    });

    /*
    dispatcher.dispatch<Pixl::WindowResizeEvent>([this](Pixl::WindowResizeEvent& e) {
        fpsController->resetMouse();
        return false;
    });
     */
}
