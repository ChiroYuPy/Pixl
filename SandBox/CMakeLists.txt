cmake_minimum_required(VERSION 3.30)
project(Sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(Sandbox src/SandBox.cpp
        src/MeshTestLayer.cpp)

target_link_libraries(Sandbox PRIVATE Pixl)