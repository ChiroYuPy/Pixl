//
// Version de debug pour diagnostiquer le problème avec la matrice viewProjection
//

#include <iostream>

#include "Pixl/Pixl.h"
#include "Pixl/Core/EntryPoint.h"

class SandboxApp : public Pixl::Application {
private:
    Pixl::Ref<Pixl::Shader> testShader;
    Pixl::Ref<Pixl::VertexArray> VAO;
    Pixl::Ref<Pixl::VertexBuffer> VBO;

    Pixl::Scope<Pixl::OrthographicCamera> camera;

public:
    explicit SandboxApp(const Pixl::ApplicationSpecification& specification)
            : Pixl::Application(specification) {
        Pixl::RenderCommand::SetClearColor({0, 1, 0, 1});

        float vertices[] = {
                0.0f,  0.5f, 0.0f,  // top
                -0.5f, -0.5f, 0.0f,  // left
                0.5f, -0.5f, 0.0f   // right
        };

        VAO = Pixl::MakeRef<Pixl::VertexArray>();
        VBO = Pixl::MakeRef<Pixl::VertexBuffer>(vertices, sizeof(vertices));

        Pixl::BufferLayout layout = {
                { Pixl::ShaderDataType::Float3, "a_position" }
        };

        VBO->SetLayout(layout);
        VAO->AddVertexBuffer(VBO);

        // Caméra orthographique avec zoom correct pour voir le triangle (-0.5 à 0.5)
        camera = Pixl::MakeScope<Pixl::OrthographicCamera>(
                GetWindow().GetAspectRatio(),
                1.0f  // zoom = 1.0f donne une zone de -aspectRatio à +aspectRatio en X, -1 à +1 en Y
        );

        // DEBUG : Afficher les valeurs de la caméra
        std::cout << "Aspect Ratio: " << GetWindow().GetAspectRatio() << std::endl;

        testShader = Pixl::MakeRef<Pixl::Shader>(
                R"(#version 330 core
            layout(location = 0) in vec3 a_position;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

            void main()
            {
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
            }
            )",
                R"(#version 330 core
            uniform vec3 u_color;
            out vec4 frag_color;
            void main()
            {
                frag_color = vec4(u_color, 1.0);
            }
            )"
        );
    }

    void OnUpdate() override {
        Pixl::RenderCommand::Clear();

        Pixl::Renderer::beginFrame(*camera);

        testShader->bind();

        glm::vec3 color = glm::vec3(0.5f, 0.1f, 1.f);
        testShader->setFloat3("u_color", color);

        // DEBUG : Afficher les matrices
        camera->setAspectRatio(GetWindow().GetAspectRatio());
        glm::mat4 projMatrix = camera->getProjectionMatrix();
        glm::mat4 viewMatrix = camera->getViewMatrix();
        glm::mat4 viewProj = projMatrix * viewMatrix;
        glm::mat4 transform = glm::mat4(1.0f);

        // Afficher les valeurs une fois au début
        static bool printed = false;
        if (!printed) {
            std::cout << "\n=== DEBUG MATRICES ===" << std::endl;

            std::cout << "Projection Matrix:" << std::endl;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    std::cout << projMatrix[j][i] << "\t";
                }
                std::cout << std::endl;
            }

            std::cout << "\nView Matrix:" << std::endl;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    std::cout << viewMatrix[j][i] << "\t";
                }
                std::cout << std::endl;
            }

            std::cout << "\nViewProjection Matrix:" << std::endl;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    std::cout << viewProj[j][i] << "\t";
                }
                std::cout << std::endl;
            }

            printed = true;
        }

        testShader->setMat4("u_viewProjection", viewProj);
        testShader->setMat4("u_transform", transform);

        VAO->bind();
        Pixl::RenderCommand::DrawArrays(Pixl::DrawMode::Triangles, 3);
        VAO->unbind();
        testShader->unbind();

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