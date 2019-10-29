//
// Created by sergi on 28/10/2019.
//

#ifndef RENDERENGINE_RENDER_H
#define RENDERENGINE_RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

class Render {

private:

    /* Variables utiles para el rendering */
    GLFWwindow *window;
    Camera *camera;
    int WIDTH;
    int HEIGHT;

public:

    /************************************
     * METODOS UTILES PARA EL RENDERING *
     ************************************/

    /* Metodo que sirve para inicializar las configuraciones de OpenGL.
     *
     * @param WIDTH Ancho de la ventana a crear
     * @param HEIGHT Alto de la ventana a crear
     */
    int init(int WIDTH, int HEIGHT);

    /* Metodo que retorna si la ventana ha sido cerrada */
    bool isWindowsClosed();

    /* Metodo que sirve para haer el swap de buffers al renderizar */
    void swapBuffers();

    /* Metodo que se encarga de limpiar la pantalla */
    void clearScreen(float R, float G, float B, float Alpha);

    /*************************************************
     * METODOS PARA DETECTAR EVENTOS EN LA SIMULACION*
     *************************************************/

    /* Metodo que se llama cuando se cambia el tamanno de la ventana */
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    /* SETTERS AND GETTERS */
    GLFWwindow *getWindow();

    void setCamera(Camera *camera);

/* Constructor and destructor */
    Render();

    ~Render();

};


#endif //RENDERENGINE_RENDER_H
