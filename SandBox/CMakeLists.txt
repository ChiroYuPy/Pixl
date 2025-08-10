cmake_minimum_required(VERSION 3.30)
project(Sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(Sandbox src/SandBox.cpp
        src/layers/CameraTestLayer.cpp
        src/layers/HueExempleLayer.cpp
        src/layers/ResourceLoadingTestLayer.cpp
        src/layers/AnimationTransformTestLayer.cpp
        src/layers/EnttTestLayer.cpp
)

target_include_directories(Pixl PUBLIC
        ${PROJECT_INCLUDE_DIR}
)

target_link_libraries(Sandbox PRIVATE Pixl)