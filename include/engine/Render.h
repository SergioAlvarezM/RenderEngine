#ifndef RENDERENGINE_RENDER_H
#define RENDERENGINE_RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Camera.h>
#include <Scene.h>
#include <EventHandler.h>

#include <Render.h>
#include <Camera.h>
#include <iostream>
#include <cstring>

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
    int init(int WIDTH, int HEIGHT)
    {

        // save the screen size
        // --------------------
        this->HEIGHT = HEIGHT;
        this->WIDTH = WIDTH;

        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

        // glfw window creation
        // --------------------
        this->window = glfwCreateWindow(WIDTH, HEIGHT, "RenderEngine", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, Render::framebuffer_size_callback);

        // tell GLFW to capture our mouse
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);

        return 1;
    }

    /* Metodo que retorna si la ventana ha sido cerrada */
    bool isWindowsClosed()
    {

        // errores
        if (this->window == nullptr)
            error("No se ha inicializado el render.");

        return glfwWindowShouldClose(this->window);
    }

    /* Metodo que se encarga de dibujar la escena */
    void drawScene()
    {

        //errores
        if (this->camera == nullptr)
            error("No se ha configurado una camara para el render");

        this->scene->drawModels(this->WIDTH, this->HEIGHT, this->camera);
    }

    /* Metodo que sirve para haer el swap de buffers al renderizar */
    void swapBuffers()
    {

        // ERRORES
        if (this->window == nullptr)
            error("No se inicializo el render");

        glfwSwapBuffers(this->getWindow());
    }

    /* Metodo que se encarga de limpiar la pantalla */
    void clearScreen(float R, float G, float B, float Alpha)
    {
        glClearColor(R, G, B, Alpha);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /*************************************************
     * METODOS PARA DETECTAR EVENTOS EN LA SIMULACION*
     *************************************************/

    /* Metodo que se llama cuando se cambia el tamanno de la ventana */
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    /* SETTERS AND GETTERS */
    GLFWwindow *getWindow()
    {
        return this->window;
    }

    void setCamera(Camera *camera)
    {
        this->camera = camera;
    }

    void setScene(Scene *scene)
    {
        this->scene = scene;
    }

    int getWidth() const
    {
        return WIDTH;
    }

    int getHeight() const
    {
        return HEIGHT;
    }

    /*********
     * UTILS *
     *********/

    /* Metodos para cambiar el titulo de la ventana */
    void setWindowsTitle(const char *title, bool showFPS)
    {

        // set the parameters.
        this->title = title;
        this->showFPS = showFPS;

        // change the window with the title
        glfwSetWindowTitle(this->window, title);
    }

    /* Metodo para actualizar el titulo, solo debe llamarse para titulos que se actualizan */
    void updateTitle(EventHandler *eventHandler)
    {

        // only update if the showFPS is true, in other case the title should not change
        if (this->showFPS)
        {

            // arreglo que tendra el titulo
            char title[100];

            // add the title of the application
            strcpy(title, this->title);

            // add the separator
            strcat(title, " - ");

            // calculate and add the frames
            std::string frames = std::to_string((int)(1 / eventHandler->getDeltaTime()));
            strcat(title, frames.c_str());

            // change the title
            glfwSetWindowTitle(this->window, title);
        }
    }

    /* Metodo que sirve para entregar un mensaje de error */
    void error(std::string msg)
    {

        std::cout << "Error: "
                  << "RENDER: " << msg << std::endl;
    }

    /* Constructor and destructor */
    Render()
    {
        camera = nullptr;
        window = nullptr;
        scene = nullptr;
    }

    ~Render()
    {
        // finish glfw when the renderer is detroyed
        glfwTerminate();
    }
};

#endif //RENDERENGINE_RENDER_H
