//
// Created by ChiroYuki on 26/07/2025.
//

#include "Pixl/Core/Application.h"
#include "Pixl/Core/Window.h"
#include "Pixl/Core/Base.h"

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

        m_Window = MakeScope<Window>(WindowSettings(m_Specification.Name));
        m_Window->SetEventCallback(makeMemberCallback(this, &Application::OnEvent));

    }

    Application::~Application() {

    }

    void Application::Close() {
        m_Running = false;
    }

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(makeMemberCallback(this, &Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(makeMemberCallback(this, &Application::OnWindowResize));
    }

    void Application::Run() {
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e) {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            return false;
        }

        // Graphics::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }

}

extern Pixl::Application* Pixl::CreateApplication();