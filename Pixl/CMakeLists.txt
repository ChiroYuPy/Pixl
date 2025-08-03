cmake_minimum_required(VERSION 3.10)
project(Pixl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GLAD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include)

set(SOURCES
        vendor/glad/src/glad.c

        src/Pixl/Core/Application.cpp
        src/Pixl/Core/Window.cpp
        src/Pixl/Core/Input.cpp

        src/Pixl/Rendering/GraphicsContext.cpp
        src/Pixl/Rendering/Renderer/Renderer.cpp
        src/Pixl/Rendering/Objects/Shader.cpp
        src/Pixl/Rendering/Objects/Buffer.cpp
        src/Pixl/Rendering/Objects/VertexArray.cpp
        src/Pixl/Rendering/RenderCommand.cpp
        src/Pixl/Rendering/Camera/PerspectiveCamera.cpp
        src/Pixl/Rendering/Material/ColorMaterial.cpp
        src/Pixl/Rendering/Mesh/StaticMesh.cpp
        src/Pixl/Rendering/Geometry/CubeGeometry.cpp
        src/Pixl/Rendering/Camera/OrthographicCamera.cpp
        src/Pixl/Rendering/Mesh/BaseMesh.cpp
        src/Pixl/Rendering/Mesh/MultiMaterialMesh.cpp
        src/Pixl/Rendering/Objects/VertexDeclaration.cpp
)

add_library(Pixl STATIC ${SOURCES})

target_include_directories(Pixl PUBLIC
        ${PROJECT_INCLUDE_DIR}
        ${GLAD_INCLUDE_DIR}
)

find_package(glfw3 REQUIRED)
target_link_libraries(Pixl PRIVATE glfw opengl32)