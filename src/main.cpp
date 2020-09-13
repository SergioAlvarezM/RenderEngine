#include <Render.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <Camera.h>
#include <EventHandler.h>
#include <GUIManager.h>

#include <iostream>

#include <Setup.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

// Functions that have to be global due to GLFW
void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera and render
Camera *camera;
Render *render;
EventHandler *eventHandler;
Scene *scene;
GUIManager *guiManager;

int main()
{

    // CREATIONS OF THE SCENE
    // ----------------------
    scene = new Scene();

    // CREATION OF RENDER
    // ------------------
    render = new Render();

    // CREATION OF THE CAMERA
    // ----------------------
    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // INIT OF RENDER
    // --------------
    render->init(SCR_WIDTH, SCR_HEIGHT);
    render->setCamera(camera);
    render->setScene(scene);

    // CREATION OF THE EVENTHANDLER
    // ----------------------------
    eventHandler = new EventHandler();
    eventHandler->setCamera(camera);
    eventHandler->setWindow(render->getWindow());
    eventHandler->setMouseCallback(mouse_callback);
    eventHandler->setScrollCallback(scroll_callback);

    // CREATION OF THE GUI MANAGER
    // ---------------------------
    guiManager = new GUIManager();
    guiManager->init(render->getWindow());

    // SETUP FUNCTION
    // --------------
    render->setWindowsTitle("RenderEngine", true);
    Setup(scene, render, camera, eventHandler);

    // render loop
    // -----------
    int a = 0;
    while (!render->isWindowsClosed())
    {

        // per-frame time logic
        // --------------------
        eventHandler->recalculateTime();
        render->updateTitle(eventHandler);

        onFrame(scene, render, camera, eventHandler);

        // input
        // -----
        eventHandler->processInput();

        // render
        // ------
        render->clearScreen(0.2f, 0.3f, 0.3f, 1.0f);
        render->drawScene();

        // gui
        // ---
        guiManager->generateFrame();
        imgui_onFrame();
        guiManager->render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        render->swapBuffers();
        eventHandler->getEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    delete render;
    delete camera;
    delete eventHandler;
    delete scene;

    // imgui: terminate imgui process
    // ------------------------------
    guiManager->destroy();

    return 0;
}

/*----------------------------------------------------------------------- ---------------------------------*/
/*------------------------FUNCIONES QUE SE DEBEN DECLARAR DE FORMA GLOBAL ---------------------------------*/
/*----------------------------------------------------------------------- ---------------------------------*/

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll((float)yoffset);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

    lastX = (float)xpos;
    lastY = (float)ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}
