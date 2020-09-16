#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <Setup.h>

#include <Settings.h>
#include <Controller.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

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
