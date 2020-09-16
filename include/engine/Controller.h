#ifndef RENDERENGINE_CONTROLLER_H
#define RENDERENGINE_CONTROLLER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Settings.h>

void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll((float)yoffset);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{

    if (firstMouse)
    {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

    lastX = (float)xpos;
    lastY = (float)ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

#endif // RENDERENGINE_CONTROLLER_H