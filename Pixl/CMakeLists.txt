cmake_minimum_required(VERSION 3.30)
project(Pixl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(VENDOR_INCLUDE_DIR vendor/include)

set(SOURCES
        vendor/src/glad/glad.c

        src/Pixl/Core/Application.cpp
        src/Pixl/Core/Window.cpp
        src/Pixl/Core/Input.cpp
        src/Pixl/Core/Layer/Layer.cpp
        src/Pixl/Core/Time/Time.cpp
        src/Pixl/Core/Time/Clock.cpp

        src/Pixl/Rendering/GraphicsContext.cpp
        src/Pixl/Rendering/Renderer/Renderer.cpp
        src/Pixl/Rendering/Objects/Shader.cpp
        src/Pixl/Rendering/Objects/Buffer.cpp
        src/Pixl/Rendering/Objects/VertexArray.cpp
        src/Pixl/Rendering/RenderCommand.cpp
        src/Pixl/Rendering/Camera/PerspectiveCamera.cpp
        src/Pixl/Rendering/Camera/OrthographicCamera.cpp
        src/Pixl/Rendering/Camera/BaseCamera.cpp
        src/Pixl/Rendering/Camera/controller/FPSController.cpp
        src/Pixl/Core/Time/Timer.cpp
        src/Pixl/Core/Time/Scheduler.cpp
        src/Pixl/Utils/Logger.cpp
        src/Pixl/Core/Layer/LayerStack.cpp
        src/Pixl/Rendering/Camera/controller/BaseCameraController.cpp
        src/Pixl/Rendering/Camera/controller/OrbitController.cpp
        src/Pixl/Rendering/Objects/VertexFormat.cpp
        src/Pixl/Rendering/Geometry/Geometry.cpp
        src/Pixl/Rendering/Material/Material.cpp
        src/Pixl/Core/Resource/FileTextureLoader.cpp
        src/Pixl/Core/Resource/Loaders/TextureLoader.cpp
        src/Pixl/Core/Resource/ResourceService.cpp
        src/Pixl/Systems/RenderSystem.cpp
        src/Pixl/Core/ECS/SceneManager.cpp
        src/Pixl/Systems/TransformSystem.cpp
        src/Pixl/Utils/PrefabRegistery.cpp
        src/Pixl/Rendering/Objects/Texture.cpp
        src/Pixl/Core/Resource/Loaders/ShaderLoader.cpp
        include/Pixl/Math/Vector2.h
)

add_library(Pixl STATIC ${SOURCES})

target_include_directories(Pixl PUBLIC
        ${PROJECT_INCLUDE_DIR}
        ${VENDOR_INCLUDE_DIR}
)

find_package(glfw3 REQUIRED)
target_link_libraries(Pixl PRIVATE glfw opengl32)