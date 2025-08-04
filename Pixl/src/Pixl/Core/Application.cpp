//
// Created by ChiroYuki on 26/07/2025.
//

#include "Pixl/Core/Base.h"
#include "Pixl/Rendering/Renderer/Renderer.h"
#include "Pixl/Core/Window.h"
#include "Pixl/Core/Application.h"
#include "Pixl/Core/Time/Clock.h"

#include <filesystem>
#include <utility>

namespace Pixl {

    Application* Application::s_Instance = nullptr;

    Application::Application(ApplicationSpecification specification)
            : m_Specification(std::move(specification))
    {
        s_Instance = this;

        if (!m_Specification.WorkingDirectory.empty())
            std::filesystem::current_path(m_Specification.WorkingDirectory);

        m_Window = makeScope<Window>(WindowSettings(m_Specification.Name));
        m_Window->setEventCallback(makeMemberCallback(this, &Application::onEvent));

        Pixl::VertexDeclaration::Initialize();
        Renderer::Init();

    }

    Application::~Application() {

    }

    void Application::close() {
        m_Running = false;
    }

    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(makeMemberCallback(this, &Application::onWindowClose));
        dispatcher.dispatch<WindowResizeEvent>(makeMemberCallback(this, &Application::onWindowResize));
    }

    void Application::run() {
        Clock clock;
        while (m_Running)
        {
            auto deltaTime = clock.restart();
            onUpdate(deltaTime);
            m_Window->onUpdate();
        }
    }

    bool Application::onWindowClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }

    bool Application::onWindowResize(WindowResizeEvent& e) {
        if (e.getWidth() == 0 || e.getHeight() == 0)
            return false;

        Renderer::OnWindowResize(e.getWidth(), e.getHeight());

        return false;
    }

}

extern Pixl::Application* Pixl::createApplication();