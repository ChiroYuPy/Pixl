//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_RENDERER_H
#define PIXLENGINE_RENDERER_H

#include "Pixl/Core/Base.h"
#include "Pixl/Rendering/Objects/Shader.h"
#include "Pixl/Rendering/Objects/VertexArray.h"
#include "Pixl/Rendering/Camera/ICamera.h"

#include <cstdint>

namespace Pixl {

    class Renderer {
    public:
        static void Init();
        static void Shutdown();

        static void OnWindowResize(uint32_t width, uint32_t height);

        static void beginFrame(ICamera& camera);
        static void endFrame();

        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

    private:
        struct SceneData {
            glm::mat4 viewProjMatrix;
            float aspectRatio;
        };

        static Scope<SceneData> s_sceneData;
    };

}

#endif //PIXLENGINE_RENDERER_H
