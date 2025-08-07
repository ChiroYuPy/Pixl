//
// Created by ChiroYuki on 05/08/2025.
//

#include "layers/MeshTestLayer.h"


void MeshTestLayer::onAttach() {
    Pixl::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    // Pixl::RenderCommand::SetPolygonMode(Pixl::PolygonMode::Line);
    Pixl::Input::setCursorMode(Pixl::CursorMode::Visible);

    // camera and cameraController init
    float aspectRatio = Pixl::Application::get().getWindow().getAspectRatio();
    camera = Pixl::MakeScope<Pixl::PerspectiveCamera>(90.0f, aspectRatio, 0.1f, 10000.0f);

    camera->setPosition({12, 12, 12});
    camera->lookAt({0, 0, 0});

    cameraController = Pixl::MakeScope<Pixl::OrbitController>(camera.get());



    auto& resourceManager = Pixl::Application::get().getResourceManager();
    try {
        // Utilisation normale
        auto tex = resourceManager.getOrLoad<Pixl::Texture>("grass.png");
        tex->use();

        // Vérification d'existence
        if (resourceManager.exists<Pixl::Texture>("grass.png"))
            std::cout << "Texture already loaded\n";

        // Rechargement forcé
        auto tex2 = resourceManager.forceReload<Pixl::Texture>("grass.png");
        tex2->use();

        // Stats
        std::cout << "Loaded textures: " << resourceManager.getLoadedCount<Pixl::Texture>() << "\n";

        // Déchargement
        resourceManager.unload<Pixl::Texture>("grass.png");
        std::cout << "After unload - Loaded textures: " << resourceManager.getLoadedCount<Pixl::Texture>() << "\n";

    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    const std::string CUBE_VERT = R"(
        #version 330 core

        layout(location = 0) in vec3 a_position;

        uniform mat4 u_viewProjection;
        uniform mat4 u_transform;

        void main()
        {
            gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
        }
    )";

    const std::string CUBE_FRAG = R"(
        #version 330 core

        uniform vec4 u_color;
        uniform float u_metallic;
        uniform float u_roughness;
        uniform vec3 u_emissive;

        out vec4 frag_color;

        void main() {
            // Exemple d'utilisation des propriétés
            vec3 finalColor = u_color.rgb + u_emissive;
            finalColor = mix(finalColor, finalColor * 0.5, u_metallic);
            finalColor = mix(finalColor, finalColor * u_roughness, 0.2);

            frag_color = vec4(finalColor, u_color.a);
        }
    )";

    // drawable object init
    Pixl::Ref<Pixl::Geometry> cubeGeometry = Pixl::Geometry::createCube();

    cubeMaterial = Pixl::MaterialFactory::createFromSource(CUBE_VERT, CUBE_FRAG);

    if (cubeMaterial) {
        cubeMaterial->setProperty("u_color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        cubeMaterial->setProperty("u_metallic", 0.8f);
        cubeMaterial->setProperty("u_roughness", 0.2f);
        cubeMaterial->setProperty("u_emissive", glm::vec3(0.1f, 0.1f, 0.0f));

        std::cout << "Available material properties:" << std::endl;
        for (const auto& name : cubeMaterial->getPropertyNames()) {
            std::cout << "  - " << name << " (type: "
                      << static_cast<int>(cubeMaterial->getPropertyType(name)) << ")" << std::endl;
        }
    }

    cubeMesh = Pixl::MakeScope<Pixl::Mesh>(cubeGeometry, cubeMaterial);
}

void MeshTestLayer::onDetach() {

}

void MeshTestLayer::onUpdate(Pixl::Time &deltaTime) {
    Pixl::RenderCommand::Clear();

    Pixl::Renderer::beginFrame(*camera);

    cameraController->update(deltaTime);

    glm::mat4 projMatrix = camera->getProjectionMatrix();
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 viewProj = projMatrix * viewMatrix;

    auto cubeTransform = glm::mat4(1.0f);
    cubeTransform = glm::translate(cubeTransform, glm::vec3(0.0f, 0.0f, 0.0f));
    cubeMesh->setTransform(cubeTransform);

    cubeMesh->render(viewProj);

    Pixl::Renderer::endFrame();
}

void MeshTestLayer::onEvent(Pixl::Event &event) {
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

    dispatcher.dispatch<Pixl::WindowResizeEvent>([this](Pixl::WindowResizeEvent& e) {
        camera->setAspectRatio(Pixl::Application::get().getWindow().getAspectRatio());
        return false;
    });
}
