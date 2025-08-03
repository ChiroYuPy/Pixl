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
    Pixl::Ref<Pixl::IndexBuffer> IBO;

    Pixl::Scope<Pixl::PerspectiveCamera> camera;

public:
    explicit SandboxApp(const Pixl::ApplicationSpecification& specification)
    : Pixl::Application(specification) {
        Pixl::RenderCommand::SetClearColor({0, 1, 0, 1});

        float vertices[] = {
                -0.5f, -0.5f, -0.5f,  // 0
                0.5f, -0.5f, -0.5f,  // 1
                0.5f,  0.5f, -0.5f,  // 2
                -0.5f,  0.5f, -0.5f,  // 3
                -0.5f, -0.5f,  0.5f,  // 4
                0.5f, -0.5f,  0.5f,  // 5
                0.5f,  0.5f,  0.5f,  // 6
                -0.5f,  0.5f,  0.5f   // 7
        };

        uint32_t Indices[] = {
                0, 1, 2, 2, 3, 0,     // back
                4, 5, 6, 6, 7, 4,     // front
                4, 5, 1, 1, 0, 4,     // bottom
                7, 6, 2, 2, 3, 7,     // top
                4, 0, 3, 3, 7, 4,     // left
                5, 1, 2, 2, 6, 5      // right
        };

        VAO = Pixl::MakeRef<Pixl::VertexArray>();
        VBO = Pixl::MakeRef<Pixl::VertexBuffer>(vertices, sizeof(vertices));
        IBO = Pixl::MakeRef<Pixl::IndexBuffer>(Indices, sizeof(Indices));

        Pixl::BufferLayout layout = {
                { Pixl::ShaderDataType::Float3, "a_position" }
        };

        VBO->SetLayout(layout);
        VAO->AddVertexBuffer(VBO);
        VAO->SetIndexBuffer(IBO);

        // Caméra orthographique avec zoom correct pour voir le triangle (-0.5 à 0.5)
        camera = Pixl::MakeScope<Pixl::PerspectiveCamera>(
                90.f, GetWindow().GetAspectRatio(), 0.1f, 10000.0f
        );
        camera->setPosition({3.0f, 3.0f, 3.0f});
        camera->lookAt({0.0f, 0.0f, 0.0f});

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
        Pixl::RenderCommand::DrawIndexed(Pixl::DrawMode::Triangles, 24);
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