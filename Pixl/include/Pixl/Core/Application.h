//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXL_APPLICATION_H
#define PIXL_APPLICATION_H

#include "Pixl/Core/Base.h"
#include "Pixl/Events/WindowEvent.h"
#include "Pixl/Events/Event.h"
#include "Pixl/Core/Window.h"
#include "Pixl/Core/Time/Time.h"
#include "Pixl/Core/Layer/Layer.h"
#include "Pixl/Core/Layer/LayerStack.h"
#include "Pixl/Core/Resource/ResourceService.h"
#include "Pixl/Core/ECS/SystemManager.h"
#include "Pixl/Core/ECS/SceneManager.h"

#include <memory>

namespace Pixl {

    struct ApplicationSpecification {
        std::string Name = "Hazel Application";
        std::string workingDirectory;
    };

    class Application {
    public:
        explicit Application(ApplicationSpecification specification);
        virtual ~Application();

        void onEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        Window& getWindow() { return *m_window; }

        ResourceService& getResourceService() { return *m_resourceService; }

        void close();

        static Application& get() { return *s_instance; }

        const ApplicationSpecification& getSpecification() const { return m_specification; }

        void run();

        Scene& createScene(std::string name);

    private:
        bool onWindowClose(WindowCloseEvent& e);
        bool onWindowResize(WindowResizeEvent& e);

    private:
        ApplicationSpecification m_specification;

        Scope<Window> m_window;
        Scope<ResourceService> m_resourceService;

        LayerStack m_LayerStack;
        SceneManager m_sceneManager;
        SystemManager m_systemManager;

        bool m_running = true;
        bool m_minimized = false;

    private:
        static Application* s_instance;
    };

    Application* createApplication();
}

#endif //PIXL_APPLICATION_H
