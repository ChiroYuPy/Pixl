cmake_minimum_required(VERSION 3.10)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Sandbox src/multiMaterialMeshTest.cpp) # select the executable

target_link_libraries(Sandbox PRIVATE Pixl)