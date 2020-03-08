//
// Created by sergi on 29/10/2019.
//

#ifndef RENDERENGINE_EVENTHANDLER_H
#define RENDERENGINE_EVENTHANDLER_H

#include <GLFW/glfw3.h>
#include <Camera.h>

/**
 * @brief Class to process all the events that occurs in the engine.
 * 
 * Class that process all the event that happens during the excecution of the engine 
 * and take action depending of the events. Support Mouse and Keyboard events.
 */
class EventHandler
{

private:
    GLFWwindow *window;
    Camera *camera;
    float lastFrame = 0;
    float deltaTime = 0;

public:
    /**
     * @brief Method to process the keyboard input of the program.
     * 
     * Process all the input of the keyboard and do actions depending on the key pressed.
     */
    void processInput();

    /* Metodo que sirve para actualizar las variables lastFrame y deltaTime del motor de rendering */
    void recalculateTime();

    /* Metodo que obtiene todos los eventos que ocurrieron en la ventana desde la ultima llamada al metodo.
    * Desde el inicio si nunca fue llamada
    */
    void getEvents();

    //-----------------------
    /* SETTERS AND GETTERS */
    // ----------------------

    /* Function must follow the following contract:
     *      void function(GLFWwindow *window, double xpos, double ypos)*/
    void setMouseCallback(GLFWcursorposfun method);

    void setScrollCallback(GLFWscrollfun method);

    void setWindow(GLFWwindow *window);

    void setCamera(Camera *camera);

    float getLastFrame() const;

    float getDeltaTime() const;

    /* CONSTRUCTORS AND DESTRUCTORS */
    EventHandler();

    ~EventHandler();
};

#endif //RENDERENGINE_EVENTHANDLER_H
