//
// Created by sergi on 29/10/2019.
//

#include "EventHandler.h"

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void EventHandler::processInput() {

    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true);

    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
        this->camera->ProcessKeyboard(FORWARD, this->deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
        this->camera->ProcessKeyboard(BACKWARD, this->deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
        this->camera->ProcessKeyboard(LEFT, this->deltaTime);
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
        this->camera->ProcessKeyboard(RIGHT, this->deltaTime);
}

void EventHandler::recalculateTime() {
    float currentFrame = glfwGetTime();
    this->deltaTime = currentFrame - this->lastFrame;
    this->lastFrame = currentFrame;
}

void EventHandler::setMouseCallback(GLFWcursorposfun method) {
    glfwSetCursorPosCallback(this->window, method);
}

void EventHandler::setScrollCallback(GLFWscrollfun method) {
    glfwSetScrollCallback(this->window, method);
}

void EventHandler::setWindow(GLFWwindow *window) {
    this->window = window;
}

void EventHandler::setCamera(Camera *camera) {
    this->camera = camera;
}

void EventHandler::getEvents() {
    glfwPollEvents();
}

EventHandler::EventHandler() {}

EventHandler::~EventHandler() {}

float EventHandler::getLastFrame() const {
    return lastFrame;
}

float EventHandler::getDeltaTime() const {
    return deltaTime;
}
