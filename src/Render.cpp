//
// Created by sergi on 28/10/2019.
//

#include "Render.h"
#include "Camera.h"
#include "EventHandler.h"
#include <GLFW/glfw3.h>
#include <iostream>

/*---------------------------------------------------------------------------------------------*/
//                                 Constructor y destructor
/*---------------------------------------------------------------------------------------------*/

Render::Render()
{
    camera = nullptr;
    window = nullptr;
    scene = nullptr;
}

Render::~Render()
{
    // finish glfw when the renderer is detroyed
    glfwTerminate();
}

/*---------------------------------------------------------------------------------------------*/
//                                 METODOS ESTATICOS
/*---------------------------------------------------------------------------------------------*/

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Render::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

/*---------------------------------------------------------------------------------------------*/
//                                 METODOS DEL PROPIO OBJETO
/*---------------------------------------------------------------------------------------------*/
int Render::init(const int WIDTH, const int HEIGHT)
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

bool Render::isWindowsClosed()
{

    // errores
    if (this->window == nullptr)
        error("No se ha inicializado el render.");

    return glfwWindowShouldClose(this->window);
}

GLFWwindow *Render::getWindow()
{
    return this->window;
}

void Render::setCamera(Camera *camera)
{
    this->camera = camera;
}

void Render::swapBuffers()
{

    // ERRORES
    if (this->window == nullptr)
        error("No se inicializo el render");

    glfwSwapBuffers(this->getWindow());
}

void Render::clearScreen(float R, float G, float B, float Alpha)
{
    glClearColor(R, G, B, Alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::drawScene()
{

    //errores
    if (this->camera == nullptr)
        error("No se ha configurado una camara para el render");

    this->scene->drawModels(this->WIDTH, this->HEIGHT, this->camera);
}

void Render::setScene(Scene *scene)
{
    this->scene = scene;
}

void Render::error(std::string msg)
{

    std::cout << "Error: "
              << "RENDER: " << msg << std::endl;
}

int Render::getWidth() const
{
    return WIDTH;
}

int Render::getHeight() const
{
    return HEIGHT;
}

void Render::setWindowsTitle(const char *title, bool showFPS)
{

    // set the parameters.
    this->title = title;
    this->showFPS = showFPS;

    // change the window with the title
    glfwSetWindowTitle(this->window, title);
}

void Render::updateTitle(EventHandler *eventHandler)
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
