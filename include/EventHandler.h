//
// Created by sergi on 29/10/2019.
//

#ifndef RENDERENGINE_EVENTHANDLER_H
#define RENDERENGINE_EVENTHANDLER_H


#include <GLFW/glfw3.h>
#include "Camera.h"

class EventHandler {

private:
    GLFWwindow *window;
    Camera *camera;
    float lastFrame = 0;
    float deltaTime = 0;

public:

    // -------------------------
    /* METHODS OF THE OBJECT */
    // -------------------------

    /* Metodo que se invoca para actualizar el input que se ingreso en el programa.*/
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
    void setMouseCallback(GLFWcursorposfun method);

    void setScrollCallback(GLFWscrollfun method);

    void setWindow(GLFWwindow *window);

    void setCamera(Camera *camera);


    /* CONSTRUCTORS AND DESTRUCTORS */
    EventHandler();

    ~EventHandler();
};


#endif //RENDERENGINE_EVENTHANDLER_H
