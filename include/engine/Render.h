#ifndef RENDERENGINE_RENDER_H
#define RENDERENGINE_RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Camera.h>
#include <Scene.h>
#include <EventHandler.h>

/**
 * @brief Class in charge of the main process of rendering a scene.
 * 
 * Class in charge of the rendering process of the program and to manage the window.
 * Join all the other components of the program to make them work together as a whole.
 * 
 */
class Render
{

private:
    /* Variables utiles para el rendering */
    GLFWwindow *window;
    Camera *camera;
    Scene *scene;

    bool showFPS;
    const char *title;

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

    /* Metodo que se encarga de dibujar la escena */
    void drawScene();

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

    void setScene(Scene *scene);

    int getWidth() const;

    int getHeight() const;

    /*********
     * UTILS *
     *********/

    /* Metodos para cambiar el titulo de la ventana */
    void setWindowsTitle(const char *title, bool showFPS);

    /* Metodo para actualizar el titulo, solo debe llamarse para titulos que se actualizan */
    void updateTitle(EventHandler *eventHandler);

    /* Metodo que sirve para entregar un mensaje de error */
    void error(std::string msg);

    /* Constructor and destructor */
    Render();

    ~Render();
};

#endif //RENDERENGINE_RENDER_H
