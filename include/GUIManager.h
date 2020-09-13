#ifndef RENDERENGINE_GUIMANAGER_H
#define RENDERENGINE_GUIMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

/**
 * @brief Class in charge of the graphic UI of the application.
 * 
 * This class is in charge of the UI of the application. This class is used in the main
 * render process to handle the GUI.
 * 
 * Class uses Dear IMGUI to manage the GUI inside opengl over glfw.
 */
class GUIManager
{

private:
    //! window to be used to render the elements.
    GLFWwindow *window;

public:
    /**
    * @brief Initialize all the parameters for the GUI to be displayed on the window.
    * 
    * Initialize IMGUI to be displayed in the screen of the window.
    * 
    * @param window 
    */
    void init(GLFWwindow *window)
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

    /**
     * @brief Generate a frame in the window to draw th user interface.
     * 
     */
    void generateFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    /**
     * @brief Destroy and set to shutdown the process related to imgui.
     * 
     */
    void destroy()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    /**
     * @brief Render the elements of the scene in the window.
     * 
     */
    void render()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    /**
     * @brief Set the Window object
     * 
     * @param window window to work with
     */
    void setWindow(GLFWwindow *window)
    {
        this->window = window;
    }
};

#endif