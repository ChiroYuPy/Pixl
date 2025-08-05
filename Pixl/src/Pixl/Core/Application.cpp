//
// Created by ChiroYuki on 26/07/2025.
//

#include "Pixl/Core/Base.h"
#include "Pixl/Rendering/Renderer/Renderer.h"
#include "Pixl/Core/Window.h"
#include "Pixl/Core/Application.h"
#include "Pixl/Core/Time/Clock.h"

#include <filesystem>
#include <ranges>
#include <utility>

namespace Pixl {

    Application* Application::s_instance = nullptr;

    Application::Application(ApplicationSpecification specification)
    : m_specification(std::move(specification)) {

        //TODO: prevent double application creation
        s_instance = this;

        if (!m_specification.workingDirectory.empty())
            std::filesystem::current_path(m_specification.workingDirectory);

        m_window = MakeScope<Window>(WindowProperties(m_specification.Name));
        m_window->setEventCallback(MakeMemberCallback(this, &Application::onEvent));

        Renderer::Init();

        // default events
        WindowResizeEvent resizeEvent(m_window->getWidth(), m_window->getHeight(), m_window->getAspectRatio());
        onEvent(resizeEvent);
    }

    Application::~Application() {
        Renderer::Shutdown();
    }


    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->onAttach();
    }

    void Application::PushOverlay(Layer* layer) {
        m_LayerStack.PushOverlay(layer);
        layer->onAttach();
    }

    void Application::close() {
        m_Running = false;
    }

    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(MakeMemberCallback(this, &Application::onWindowClose));
        dispatcher.dispatch<WindowResizeEvent>(MakeMemberCallback(this, &Application::onWindowResize));

        for (auto & it : std::ranges::reverse_view(m_LayerStack)) {
            if (e.Handled) break;
            it->onEvent(e);
        }
    }

    void Application::run() {
        Clock clock;

        while (m_Running) {
            Time deltaTime = clock.restart();

            if (!m_minimized) {
                for (Layer* layer : m_LayerStack)
                    layer->onUpdate(deltaTime);
            }

            m_window->onUpdate();
        }
    }

    bool Application::onWindowClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }

    bool Application::onWindowResize(WindowResizeEvent& e) {
        if (e.getWidth() == 0 || e.getHeight() == 0) {
            m_minimized = true;
            return false;
        }

        m_minimized = false;

        Renderer::OnWindowResize(e.getWidth(), e.getHeight());

        return false;
    }

}

extern Pixl::Application* Pixl::createApplication();