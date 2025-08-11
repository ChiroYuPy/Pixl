//
// Created by ChiroYuki on 01/08/2025.
//

#ifndef PIXLENGINE_RENDERER_H
#define PIXLENGINE_RENDERER_H

#include "Pixl/Core/Base.h"
#include "Pixl/Rendering/Objects/Shader.h"
#include "Pixl/Rendering/Objects/VertexArray.h"
#include "Pixl/Rendering/Camera/ICamera.h"
#include "Pixl/Rendering/Material/Material.h"
#include "Pixl/Rendering/Geometry/Geometry.h"

#include <cstdint>

namespace Pixl {

    struct RenderStats {
        uint32_t drawCalls = 0;
        uint32_t triangles = 0;

        void reset() {
            drawCalls = 0;
            triangles = 0;
        }
    };

    class Renderer {
    public:
        static void init();
        static void shutdown();

        static void onWindowResize(uint32_t width, uint32_t height);

        static void setActiveCamera(const Ref <ICamera> &camera);

        static void beginFrame();
        static void endFrame();

        static void submit(const Ref<Material> &material, const Ref<Geometry>& geometry, const glm::mat4& transform);

        static void flush();

        static const RenderStats& getStats() { return s_stats; }
        static void resetStats() { s_stats.reset(); }

    private:
        struct SceneData {
            Ref<ICamera> camera;
            float aspectRatio;
        };

        struct RenderCommandData {
            Ref<Material> material;
            Ref<Geometry> geometry;
            glm::mat4 transform;
        };

        static RenderStats s_stats;
        static Scope<SceneData> s_sceneData;
        static std::vector<RenderCommandData> s_renderQueue;
    };

}

#endif //PIXLENGINE_RENDERER_H
