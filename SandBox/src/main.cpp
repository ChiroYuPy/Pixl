//
// Created by ChiroYuki on 26/07/2025.
//

#include <iostream>

#include "Pixl/Pixl.h"
#include "Pixl/Core/EntryPoint.h"

class SandboxApp : public Pixl::Application {
private:
    Pixl::Ref<Pixl::Shader> testShader;
    Pixl::Scope<Pixl::PerspectiveCamera> camera;

    Pixl::Ref<Pixl::VertexArray> VAO;
    Pixl::Ref<Pixl::VertexBuffer> VBO;

public:
    explicit SandboxApp(const Pixl::ApplicationSpecification& specification)
            : Pixl::Application(specification) {
        Pixl::RenderCommand::SetClearColor({0, 1, 1, 1});

        // ------------ [ begin render ] ------------ //

        float vertices[] = {
                // positions
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

        // ------------ [ end render ] ------------ //


        camera = Pixl::MakeScope<Pixl::PerspectiveCamera>(90.f, GetWindow().GetAspectRatio(), 0.1f, 1000.f);

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

        glm::vec3 color = glm::vec3(0.5f, 0.1f, 1.f);
        testShader->setFloat3("u_color", color);

        glm::mat4 transform = glm::mat4(1.0f);

        Pixl::Renderer::Submit(testShader, VAO, transform);

        Pixl::Renderer::endFrame();
    }

    ~SandboxApp() override = default;
};

Pixl::Application* Pixl::CreateApplication() {
    ApplicationSpecification spec;
    spec.Name = "SandboxApp";
    spec.WorkingDirectory = R"(C:\Users\ChiroYuki\CLionProjects\Pixl\SandBox\resources)";

    return new SandboxApp(spec);
}