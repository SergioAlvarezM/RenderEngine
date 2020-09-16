/**
 * @file Controller.h
 * @author Sergio Alvarez Medina (ser.alvarez1998@gmail.com)
 * @brief File with all the functions to be used for glfw to process events. (require event manager to connect them with glfw).
 * @version 0.1
 * @date 2020-09-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef RENDERENGINE_CONTROLLER_H
#define RENDERENGINE_CONTROLLER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Settings.h>
#include <spdlog/spdlog.h>

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void mouse_callback_do_nothing(GLFWwindow *window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);

/**
 * @brief Callback function for the scrolling of the mouse.
 * 
 * @param window Window to be used.
 * @param xoffset X offset of the scrolling.
 * @param yoffset Y offset of the scrolling.
 */
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll((float)yoffset);
}

/**
 * @brief Callback function for the mouse movement that does nothing.
 * 
 * @param window Window to be used.
 * @param xpos xpos of the mouse.
 * @param ypos ypos of the mouse.
 */
void mouse_callback_do_nothing(GLFWwindow *window, double xpos, double ypos)
{
    return;
}

/**
 * @brief Mouse button callback to control the actions.
 * 
 * @param window Window to be used.
 * @param button Button pressed.
 * @param action Action over the button.
 * @param mods Modifier bits.
 */
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    // move the camera if the click is pressed
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        spdlog::info("Pressed mouse left button.");
        firstMouse = true;
        eventHandler->setMouseCallback(mouse_callback);
    }

    // dont move camera if click is unpressed
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        spdlog::info("Released mouse left button");
        eventHandler->setMouseCallback(mouse_callback_do_nothing);
    }
}

/**
 * @brief Mouse button callback that does nothing.
 * 
 * @param window Window to be used.
 * @param button Button pressed.
 * @param action Action over the button.
 * @param mods Modifier bits.
 */
void mouse_button_callback_do_nothing(GLFWwindow *window, int button, int action, int mods)
{
    return;
}

/**
 * @brief Callback function for the mouse movement that moves the camera.
 * 
 * @param window Window to be used.
 * @param xpos xpos of the mouse.
 * @param ypos ypos of the mouse.
 */
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