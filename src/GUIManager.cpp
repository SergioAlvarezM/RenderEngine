
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <GUIManager.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

void GUIManager::init(GLFWwindow *window)
{

    this->setWindow(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Fonts
    io.Fonts->AddFontDefault();
}

void GUIManager::generateFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUIManager::destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUIManager::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIManager::setWindow(GLFWwindow *window)
{
    this->window = window;
}
