//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXL_APPLICATION_H
#define PIXL_APPLICATION_H

#include "Pixl/Core/Base.h"
#include "Pixl/Events/ApplicationEvent.h"
#include "Pixl/Events/Event.h"
#include "Pixl/Core/Window.h"

#include <memory>

namespace Pixl {

    struct ApplicationSpecification
    {
        std::string Name = "Hazel Application";
        std::string WorkingDirectory;
    };

    class Application {
    public:
        Application(ApplicationSpecification  specification);
        virtual ~Application();

        void OnEvent(Event& e);

        Window& GetWindow() { return *m_Window; }

        void Close();

        static Application& Get() { return *s_Instance; }

        const ApplicationSpecification& GetSpecification() const { return m_Specification; }

        void Run();

        virtual void OnUpdate() {}

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        ApplicationSpecification m_Specification;
        Scope<Window> m_Window;
        bool m_Running = true;

    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}

#endif //PIXL_APPLICATION_H
