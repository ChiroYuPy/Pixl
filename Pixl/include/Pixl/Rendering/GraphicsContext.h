//
// Created by ChiroYuki on 26/07/2025.
//

#ifndef PIXLENGINE_GRAPHICSCONTEXT_H
#define PIXLENGINE_GRAPHICSCONTEXT_H

struct GLFWwindow;

namespace Pixl {

    class GraphicsContext {
    public:
        GraphicsContext(GLFWwindow* windowHandle);

        void Init();
        void SwapBuffers();
    private:
        GLFWwindow* m_WindowHandle;
    };
}

#endif //PIXLENGINE_GRAPHICSCONTEXT_H
