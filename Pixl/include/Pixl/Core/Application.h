//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXL_APPLICATION_H
#define PIXL_APPLICATION_H

#include "Pixl/Core/Base.h"
#include "Pixl/Events/ApplicationEvent.h"
#include "Pixl/Events/MouseEvent.h"
#include "Pixl/Events/KeyEvent.h"
#include "Pixl/Events/Event.h"
#include "Pixl/Core/Window.h"
#include "Pixl/Core/Time/Time.h"

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

        virtual void onEvent(Event& e);

        virtual void onUpdate(const Pixl::Time& deltaTime) {}

        Window& getWindow() { return *m_Window; }

        void close();

        static Application& get() { return *s_Instance; }

        const ApplicationSpecification& getSpecification() const { return m_Specification; }

        void run();

    private:
        bool onWindowClose(WindowCloseEvent& e);
        bool onWindowResize(WindowResizeEvent& e);

    private:
        ApplicationSpecification m_Specification;
        Scope<Window> m_Window;
        bool m_Running = true;

    private:
        static Application* s_Instance;
    };

    Application* createApplication();
}

#endif //PIXL_APPLICATION_H
