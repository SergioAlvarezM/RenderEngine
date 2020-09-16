#ifndef RENDERENGINE_SETTINGS_H
#define RENDERENGINE_SETTINGS_H

#include <Render.h>
#include <Camera.h>
#include <EventHandler.h>
#include <GUIManager.h>

// glfw: window settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// glfw: mouse callback settings
// -------------------------------------------------------
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Camera and render and other global pointers
Camera *camera;
Render *render;
EventHandler *eventHandler;
Scene *scene;
GUIManager *guiManager;

#endif // RENDERENGINE_SETTINGS_H