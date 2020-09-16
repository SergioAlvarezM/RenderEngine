/** Code Instructions
 *
 * This code is the one that will be excecuted in the beggining and in each frame.
 *
 * The function setup is called only once y the beggining of the process and the onFrame function will be called
 * in each frame of the aplication.
 */

#ifndef RENDERENGINE_SETUP_H
#define RENDERENGINE_SETUP_H

#include <Render.h>
#include <Shader.h>
#include <Model.h>
#include <Scene.h>
#include <EventHandler.h>
#include <Setup.h>

#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

// Global variables
// --------------------------------------------------------------------------------------------
Shader *ourShader;
Shader *other_ourShader;
Shader *juliaShader;
Shader *mandelbrotShader;

Model *m1;
Model *m2;
Model *m3;
Model *m4;
Model *m5;

/**
 * @brief Function called at the beggining of the rendering process once.
 * 
 * @param scene Scene to draw in the engine.
 * @param render Render object used by the engine.
 * @param camera Camera used by the engine.
 * @param eventHandler Handler of the events used by the engine.
 */
void Setup(Scene *scene, Render *render, Camera *camera, EventHandler *eventHandler)
{

    // build and compile our shader zprogram
    // ------------------------------------
    ourShader = new Shader("./Shaders/VertexShader.glsl", "./Shaders/PixelShader.glsl");
    other_ourShader = new Shader("./Shaders/VertexShader.glsl", "./Shaders/PixelShader.glsl");
    juliaShader = new Shader("./Shaders/VertexShader.glsl", "./Shaders/PixelJulia.glsl");
    mandelbrotShader = new Shader("./Shaders/VertexShader.glsl", "./Shaders/PixelMandelbrot.glsl");

    // CREATION OF MODELS TO DRAW
    // --------------------------

    // vertex of a cube
    float vertices[] = {
        -0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,

        -0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,

        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,

        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,

        -0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        0.5f,
        -0.5f,
        -0.5f,
        -0.5f,

        -0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        0.5f,
        -0.5f,
        0.5f,
        -0.5f,
    };

    m1 = new Model();
    m1->setVertex(std::vector<float>(vertices, vertices + sizeof(vertices) / sizeof(vertices[0])));
    m1->setShader(ourShader);
    scene->addModel(m1);

    // create a second object
    m2 = new Model();
    m2->setVertex(std::vector<float>(vertices, vertices + sizeof(vertices) / sizeof(vertices[0])));
    m2->setShader(mandelbrotShader);
    scene->addModel(m2);
    m2->setPos(glm::vec3(2, 0, 0));

    // create a third object
    m3 = new Model();
    m3->setVertex(std::vector<float>(vertices, vertices + sizeof(vertices) / sizeof(vertices[0])));
    m3->setShader(mandelbrotShader);
    scene->addModel(m3);
    m3->setPos(glm::vec3(-2, 0, 0));

    // create a fourth object
    m4 = new Model();
    m4->setVertex(std::vector<float>(vertices, vertices + sizeof(vertices) / sizeof(vertices[0])));
    m4->setShader(juliaShader);
    scene->addModel(m4);
    m4->setPos(glm::vec3(0, 2, 0));

    // create a fifth object
    m5 = new Model();
    m5->loadFile("models/Teapot.obj"); // load vertex
    m5->setShader(other_ourShader);
    scene->addModel(m5);
    m5->setPos(glm::vec3(5, 2, 0));

    // add the axis to the scene
    scene->addAxis();
}

/**
 * @brief Function called in every frame of the rendering process.
 * 
 * @param scene Scene to draw in the engine.
 * @param render Render object used by the engine.
 * @param camera Camera used by the engine.
 * @param eventHandler Handler of the events used by the engine.
 */
void onFrame(Scene *scene, Render *render, Camera *camera, EventHandler *eventHandler)
{
    // put here code that will be excecuted in every frame

    mandelbrotShader->setFloat("iTime", eventHandler->getLastFrame());
    mandelbrotShader->setVec3("iResolution", glm::vec3(render->getWidth(), render->getHeight(), 1));

    juliaShader->setFloat("iTime", eventHandler->getLastFrame());
    juliaShader->setVec3("iResolution", glm::vec3(render->getWidth(), render->getHeight(), 1));
}

/**
 * @brief Function called on each frame to manage the imgui interface.
 * 
 */
void imgui_onFrame()
{
    // window
    ImGui::Begin("Demo window");
    ImGui::Button("Hello!");
    ImGui::End();

    // window
    ImGui::Begin("Demo window ajajajajjaja long");
    ImGui::Button("Hello!");
    ImGui::End();
}

#endif