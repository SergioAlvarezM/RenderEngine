/**
 * @file EventHandler.h
 * @author Sergio Alvarez Medina (ser.alvarez1998@gmail.com)
 * @brief File with the EventHandler class. Manage all the events of the engine.
 * @version 0.1
 * @date 2020-09-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef RENDERENGINE_EVENTHANDLER_H
#define RENDERENGINE_EVENTHANDLER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Camera.h>
#include <stdio.h>

/**
 * @brief Class to process all the events that occurs in the engine.
 * 
 * Process all the event that happens during the excecution of the engine 
 * and take action depending of the events via the methods defined by the user.
 * 
 * Support Mouse and Keyboard events.
 * 
 * To work it needs a Window and Camera Objects to be defined via the setters methods.
 */
class EventHandler
{

private:
    GLFWwindow *window;
    Camera *camera;
    float lastFrame = 0;
    float deltaTime = 0;

public:
    /**
     * @brief Method to process the keyboard input of the program.
     * 
     * Process all the input of the keyboard and do actions depending on the key pressed.
     */
    void processInput()
    {

        if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(this->window, true);

        if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
            this->camera->ProcessKeyboard(Camera::Movement::FORWARD, this->deltaTime);
        if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
            this->camera->ProcessKeyboard(Camera::Movement::BACKWARD, this->deltaTime);
        if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
            this->camera->ProcessKeyboard(Camera::Movement::LEFT, this->deltaTime);
        if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
            this->camera->ProcessKeyboard(Camera::Movement::RIGHT, this->deltaTime);
    }

    /**
     * @brief Update the variables that control the timing of the engine.
     * 
     * Update the lastFrame and deltaTime variables.
     */
    void recalculateTime()
    {
        float currentFrame = (float)glfwGetTime();
        this->deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;
    }

    /**
    * @brief Call glfw to get the events that happened in the engine.
    * 
    * Get the events that happened since the last call of this method. If the method 
    * has never been called then obtain all the events that happened since the 
    * beggining of the engine.
    */
    void getEvents()
    {
        glfwPollEvents();
    }

    /**
     * @brief Set the Mouse Callback object.
     * 
     * Set the mouse Callback method to excecute in a Mouse Click event.
     * The method should follow the following contract: void function(GLFWwindow *window, double xpos, double ypos).
     * 
     * @param method Method to execute when a mouse event is encounter.
     */
    void setMouseCallback(GLFWcursorposfun method)
    {
        glfwSetCursorPosCallback(this->window, method);
    }

    /**
     * @brief Set the Mouse Button Callback object.
     * 
     * @param method Method to be called when there is a mouse callback.
     */
    void setMouseButtonCallback(GLFWmousebuttonfun method)
    {
        glfwSetMouseButtonCallback(this->window, method);
    }

    /**
     * @brief Set the Scroll Callback object.
     * 
     * Set the Mouse Scroll Event callback function to excecute in a Mouse Scroll 
     * Event. The method should follow the following contract: void function(GLFWwindow *window, double xscroll, double yscroll).
     * 
     * @param method Method to execute when a mouse scroll event is encounter.
     */
    void setScrollCallback(GLFWscrollfun method)
    {
        glfwSetScrollCallback(this->window, method);
    }

    /**
     * @brief Set the Keyboard Callback object.
     * 
     * Set the callback function for the keyboards events.
     * 
     * @param method Method to execute when a key event happens.
     */
    void setKeyboardCallback(GLFWkeyfun method)
    {
        glfwSetKeyCallback(this->window, method);
    }

    /**
     * @brief Set the Window object.
     * 
     * @param window Window object that is being used by the engine.
     */
    void setWindow(GLFWwindow *window)
    {
        this->window = window;
    }

    /**
     * @brief Set the Camera object.
     * 
     * @param camera Camera object that is being used by the engine.
     */
    void setCamera(Camera *camera)
    {
        this->camera = camera;
    }

    /**
     * @brief Get the Last Frame variable.
     * 
     * Get the time when the last frame was executed.
     * 
     * @return float Time when the last frame was executed.
     */
    float getLastFrame() const
    {
        return lastFrame;
    }

    /**
     * @brief Get the Delta Time variable.
     * 
     * Get the time between the last frame and the current frame.
     * 
     * @return float Time between last frame and current frame.
     */
    float getDeltaTime() const
    {
        return deltaTime;
    }

    /**
     * @brief Print a message of information in the console.
     * 
     * @param message Message to be printed
     */
    void info(std::string message)
    {
        std::cout << "EventHandler::" << message << std::endl;
    }

    /**
     * @brief Construct a new Event Handler object
     * 
     */
    EventHandler() {}

    /**
     * @brief Destroy the Event Handler object
     * 
     */
    ~EventHandler() {}
};

#endif //RENDERENGINE_EVENTHANDLER_H
