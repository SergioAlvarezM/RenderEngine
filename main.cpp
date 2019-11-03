#include <Render.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <Shader.h>
#include <Camera.h>
#include <EventHandler.h>

#include <iostream>

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
Scene* scene;

int main() {

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

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("./Shaders/VertexShader.glsl", "./Shaders/PixelShader.glsl");
    Shader juliaShader("./Shaders/VertexShader.glsl","./Shaders/PixelJulia.glsl");
    Shader mandelbrotShader("./Shaders/VertexShader.glsl","./Shaders/PixelMandelbrot.glsl");


    // CREATION OF MODELS TO DRAW
    // --------------------------

    // vertex of a cube
    float vertices[] =  {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,

            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,

            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
    };

    Model m1 = Model();
    m1.setVertex(std::vector<float>(vertices,vertices + sizeof(vertices)/ sizeof(vertices[0])));
    m1.setShader(&mandelbrotShader);
    scene->addModel(&m1);


    // create a second object
    Model m2 = Model();
    m2.setVertex(std::vector<float>(vertices,vertices + sizeof(vertices)/ sizeof(vertices[0])));
    m2.setShader(&ourShader);
    scene->addModel(&m2);
    m2.setPos(glm::vec3(2,0,0));


    // create a third object
    Model m3 = Model();
    m3.setVertex(std::vector<float>(vertices,vertices + sizeof(vertices)/ sizeof(vertices[0])));
    m3.setShader(&mandelbrotShader);
    scene->addModel(&m3);
    m3.setPos(glm::vec3(-2,0,0));


    // create a fourth object
    Model m4 = Model();
    m4.setVertex(std::vector<float>(vertices,vertices + sizeof(vertices)/ sizeof(vertices[0])));
    m4.setShader(&juliaShader);
    scene->addModel(&m4);
    m4.setPos(glm::vec3(0,2,0));


    // render loop
    // -----------
    int a = 0;
    while (!render->isWindowsClosed()) {


        // per-frame time logic
        // --------------------
        eventHandler->recalculateTime();

        mandelbrotShader.setFloat("iTime",eventHandler->getLastFrame());
        mandelbrotShader.setVec3("iResolution",glm::vec3(render->getWidth(),render->getHeight(),1));

        juliaShader.setFloat("iTime",eventHandler->getLastFrame());
        juliaShader.setVec3("iResolution",glm::vec3(render->getWidth(),render->getHeight(),1));

        // input
        // -----
        eventHandler->processInput();

        // render
        // ------
        render->clearScreen(0.2f,0.3f,0.3f,1.0f);
        render->drawScene();

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

    return 0;
}

/*----------------------------------------------------------------------- ---------------------------------*/
/*------------------------FUNCIONES QUE SE DEBEN DECLARAR DE FORMA GLOBAL ---------------------------------*/
/*----------------------------------------------------------------------- ---------------------------------*/

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera->ProcessMouseScroll(yoffset);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}


