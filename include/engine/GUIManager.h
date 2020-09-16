#ifndef RENDERENGINE_GUIMANAGER_H
#define RENDERENGINE_GUIMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    * Initialize IMGUI to be displayed in the screen of the window. Window can be changed with the setWindow method.
    * 
    * @param window Window to use in the rendering process.
    */
    void init(GLFWwindow *window);

    /**
     * @brief Generate a frame in the window to draw th user interface.
     * 
     */
    void generateFrame();

    /**
     * @brief Destroy and set to shutdown the process related to imgui.
     * 
     */
    void destroy();

    /**
     * @brief Render the elements of the scene in the window.
     * 
     */
    void render();

    /**
     * @brief Set the Window object
     * 
     * @param window window to work with
     */
    void setWindow(GLFWwindow *window);
};

#endif