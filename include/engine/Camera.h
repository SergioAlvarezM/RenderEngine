//
// Created by sergi on 28/10/2019.
//

#ifndef RENDERENGINE_CAMERA_H
#define RENDERENGINE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include <stdio.h>
#include <vector>

// Default camera values

/** 
 * Initial value of the camera variables.
 * 
 * Shouldn't be harcoded. This is only to make the code more readable
 * and easy to modify.
 */
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

/**
 * @brief Class to control the Camera of the engine.
 * 
 * An abstract camera class that processes input and calculates the corresponding Euler Angles, 
 * Vectors and Matrices for use in OpenGL.
 */
class Camera
{
public:
    // Camera Attributes
    //------------------

    //! Position of the camera.
    glm::vec3 Position;
    //! Direction of the front of the camera.
    glm::vec3 Front;
    //! Direction of the vertical axis of the camera.
    glm::vec3 Up;
    //! Direction of the horizontal axis of the camera.
    glm::vec3 Right;
    //! Direction of the vertical axis of the world.
    glm::vec3 WorldUp;

    // Euler Angles
    //-------------

    //! Rotation in the Y-Axis of the camera.
    float Yaw;
    //! Rotation in the X-Axis of the camera.
    float Pitch;

    // Camera options
    //---------------

    //! Movement speed of the camera.
    float MovementSpeed;
    //! Sensivity of the mouse.
    float MouseSensitivity;
    //! Zoom of the camera view.
    float Zoom;

    /**
     * @brief Enum to indicate the posible movements of the camera.
     * 
     * Defines several possible options for camera movement. 
     * Used as abstraction to stay away from window-system specific input methods.
     */
    enum class Movement
    {
        //! Movement towards the front.
        FORWARD,
        //! Movement backwards.
        BACKWARD,
        //! Movement to the left.
        LEFT,
        //! Movement to the right.
        RIGHT
    };

    /**
     * @brief Construct a new Camera object
     * 
     * Constructor of the Camera object. 
     * The camera always began looking to the -Z Axis, Y-Axis must be defined in order to 
     * set correctly the camera coordinate system.
     * 
     * @param position Initial position of the camera.
     * @param up Vector with the direction in the positive z-axis. Can be changed for testing others configurations.
     * @param yaw Rotation in the Y-Axis.
     * @param pitch Rotation in the X-Axis.
     */
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    /**
     * @brief Construct a new Camera object
     * 
     * Constructor of the Camera object. 
     * The camera always began looking to the -Z Axis, Y-Axis must be defined in order to 
     * set correctly the camera coordinate system.
     * 
     * @param posX Position in the X-Axis of the camera.
     * @param posY Position in the Y-Axis of the camera.
     * @param posZ Position in the Z-Axis of the camera.
     * @param upX X component of the vector indicating the Y world axis.
     * @param upY Y component of the vector indicating the Y world axis.
     * @param upZ Z component of the vector indicating the Y world axis.
     * @param yaw Rotation in the Y-Axis.
     * @param pitch Rotation in the X-Axis.
     */
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    /**
     * @brief Get the View Matrix object
     * 
     * Returns the view matrix calculated using Euler Angles and the LookAt Matrix.
     * 
     * @return glm::mat4 View matrix of the camera.
     */
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    //

    /**
     * @brief Process the input of the keyboard.
     * 
     * Processes input received from any keyboard-like input system. 
     * Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
     * 
     * @param direction Direction in wich the camera is moving.
     * @param deltaTime Amount of time passed since the interaction.
     */
    void ProcessKeyboard(Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == Movement::FORWARD)
            Position += Front * velocity;
        if (direction == Movement::BACKWARD)
            Position -= Front * velocity;
        if (direction == Movement::LEFT)
            Position -= Right * velocity;
        if (direction == Movement::RIGHT)
            Position += Right * velocity;
    }

    /**
     * @brief Process the input received from the mouse.
     * 
     * Processes input received from a mouse input system. 
     * Expects the offset value in both the x and y direction.
     * 
     * @param xoffset Movement in the X-axis (screen coordinate system).
     * @param yoffset Movement in the Y-axis (screen coordinate system).
     * @param constrainPitch When true dont allow to exceed 90 degrees of rotation in the X axis.
     */
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    /**
     * @brief Process the mouse scroll.
     * 
     * Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
     * 
     * @param yoffset Offset of the scroll of the mouse.
     */
    void ProcessMouseScroll(float yoffset)
    {
        if (Zoom >= 1.0f && Zoom <= 45.0f)
            Zoom -= yoffset;
        if (Zoom <= 1.0f)
            Zoom = 1.0f;
        if (Zoom >= 45.0f)
            Zoom = 45.0f;
    }

private:
    /**
     * @brief Recalculate the vectors of the camera.
     * 
     * Calculates the front vector from the Camera's (updated) Euler Angles, 
     * also calculates the Right and Up vector of the camera.
     */
    void updateCameraVectors()
    {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // Also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp)); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif //RENDERENGINE_CAMERA_H
