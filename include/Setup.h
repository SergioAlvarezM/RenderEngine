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

/**
 * @brief Function called at the beggining of the rendering process once.
 * 
 * @param scene Scene to draw in the engine.
 * @param render Render object used by the engine.
 * @param camera Camera used by the engine.
 * @param eventHandler Handler of the events used by the engine.
 */
void Setup(Scene *scene, Render *render, Camera *camera, EventHandler *eventHandler);

/**
 * @brief Function called in every frame of the rendering process.
 * 
 * @param scene Scene to draw in the engine.
 * @param render Render object used by the engine.
 * @param camera Camera used by the engine.
 * @param eventHandler Handler of the events used by the engine.
 */
void onFrame(Scene *scene, Render *render, Camera *camera, EventHandler *eventHandler);

/**
 * @brief Function called on each frame to manage the imgui interface.
 * 
 */
void imgui_onFrame();

#endif