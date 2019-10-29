//
// Created by sergi on 28/10/2019.
//

#include "Render.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>


/*---------------------------------------------------------------------------------------------*/
//                                 Constructor y destructor
/*---------------------------------------------------------------------------------------------*/

Render::Render() {}

Render::~Render() {
    // finish glfw when the renderer is detroyed
    glfwTerminate();
}


/*---------------------------------------------------------------------------------------------*/
//                                 METODOS ESTATICOS
/*---------------------------------------------------------------------------------------------*/

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Render::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


/*---------------------------------------------------------------------------------------------*/
//                                 METODOS DEL PROPIO OBJETO
/*---------------------------------------------------------------------------------------------*/
int Render::init(const int WIDTH, const int HEIGHT) {

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
    if (window == NULL) {
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
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    return 1;
}

bool Render::isWindowsClosed() {
    return glfwWindowShouldClose(this->window);
}

GLFWwindow *Render::getWindow() {
    return this->window;
}

void Render::setCamera(Camera *camera) {
    this->camera = camera;
}

void Render::swapBuffers() {

    glfwSwapBuffers(this->getWindow());

}

void Render::clearScreen(float R, float G, float B, float Alpha) {
    glClearColor(R,G,B,Alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
