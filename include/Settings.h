/**
 * @file Settings.h
 * @author Sergio Alvarez Medina (ser.alvarez1998@gmail.com)
 * @brief File that contains all the global variables of the engine.
 * @version 0.1
 * @date 2020-09-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef RENDERENGINE_SETTINGS_H
#define RENDERENGINE_SETTINGS_H

#include <Render.h>
#include <Camera.h>
#include <EventHandler.h>
#include <GUIManager.h>

// glfw: window settings
// ---------------------

//! Width of the screen
const unsigned int SCR_WIDTH = 800;

//! Height of the screen
const unsigned int SCR_HEIGHT = 600;

// glfw: mouse callback settings
// -------------------------------------------------------

//! Variable to cath the mouse movement on the screen on the x-axis
float lastX = SCR_WIDTH / 2.0f;

//! Variable to cath the mouse movement on the screen on the y-axis
float lastY = SCR_HEIGHT / 2.0f;

//! Variable that indicate if the mouse has been moved before.
bool firstMouse = true;

// Camera and render and other global pointers
// -------------------------------------------

//! Camera of the engine in the main program
Camera *camera;

//! Render of the engine in the main program
Render *render;

//! EventHandler of the engine in the main program
EventHandler *eventHandler;

//! Scene of the engine in the main program
Scene *scene;

//! GUIManager of the engine in the main program
GUIManager *guiManager;

#endif // RENDERENGINE_SETTINGS_H