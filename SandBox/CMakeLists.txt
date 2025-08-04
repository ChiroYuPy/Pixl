cmake_minimum_required(VERSION 3.30)
project(Sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Sandbox src/meshTest.cpp) # select the executable

target_link_libraries(Sandbox PRIVATE Pixl)