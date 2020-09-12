cmake_minimum_required(VERSION 3.10)
project(RenderEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

# Global variables
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add another projects to compile
add_subdirectory(libs/glfw-3.3)

# Add paths to the directories to search for the hpp files
include_directories("include")
include_directories("libs/glm")
include_directories("libs/glad/include")

# Search the source files
file(GLOB sourcefiles
        "src/*.cpp")

# Copy the files used in the compilation
file(COPY Shaders/Pixel_SimplePosAndColor.glsl DESTINATION Shaders)
file(COPY Shaders/PixelJulia.glsl DESTINATION Shaders)
file(COPY Shaders/PixelMandelbrot.glsl DESTINATION Shaders)
file(COPY Shaders/PixelShader.glsl DESTINATION Shaders)
file(COPY Shaders/Vertex_SimplePosAndColor.glsl DESTINATION Shaders)
file(COPY Shaders/VertexShader.glsl DESTINATION Shaders)
file(COPY models/Sofa.obj DESTINATION models)
file(COPY models/Teapot.obj DESTINATION models)
file(COPY models/Gastly.obj DESTINATION models)

add_executable(RenderEngine glad.c ${sourcefiles})

target_link_libraries(RenderEngine glfw)