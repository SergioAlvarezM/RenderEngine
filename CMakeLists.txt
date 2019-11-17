cmake_minimum_required(VERSION 3.15)
project(RenderEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories("include")
include_directories("libs/glm")
include_directories("libs/glad/include")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw-3.3)

add_executable(RenderEngine main.cpp glad.c include/Scene.cpp include/Scene.h include/Render.cpp include/Render.h include/Camera.h include/Shader.h include/EventHandler.cpp include/EventHandler.h include/Model.cpp include/Model.h Setup.h)

target_link_libraries(RenderEngine glfw)