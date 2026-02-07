#pragma once
#ifndef CAMERA_H
#define CAMERA_H
//
#include<glad/glad.h>
#include<iostream>
//glm setup
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};
// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 0.5f;
const float SENSITIVITY = 1.0f;


class Camera {
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Constructors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    // Public methods
    glm::mat4 GetViewMatrix();
    glm::vec3 getCameraPos();
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

private:
    void updateCameraVectors();
};

#endif

