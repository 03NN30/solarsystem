#include "camera.hpp"
#include <cmath>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include <iostream>

static bool firstFollowing = true;

Camera::Camera() {
    updateCameraVectors();
}

void Camera::processMouseMotion(float xoffset, float yoffset) {
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;
    
    if (yaw > 360.0f) {
        yaw = fmod(yaw, 360.0f);
    }
    if (yaw < 0.0f) {
        yaw = 360.0f + fmod(yaw, 360.0f);
    }
    
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::proessKeyboard(m_Camera direction, float cameraSpeed) {
    switch (direction) {
    case m_forwards:
        position += front * cameraSpeed;
    break;
    case m_backwards:
        position -= front * cameraSpeed;
    break;
    case m_left:
        position -= right * cameraSpeed; 
    break;
    case m_right:
        position += right * cameraSpeed;
    break;
    case m_up:
        position = glm::vec3(position[0], position[1] + cameraSpeed, position[2]);
    break;
    case m_down:
        position = glm::vec3(position[0], position[1] - cameraSpeed, position[2]);
    break;
    }
}

void Camera::follow(glm::fmat4 &mat, f_Camera direction, float size) {
    glm::mat4 transformation = mat; 
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(transformation, scale, rotation, translation, skew, perspective);
    switch (direction) {
    case f_front:
        yaw = 90.0f;
        pitch = 0.0f;
        position = glm::vec3(translation[0], translation[1], translation[2] - size);
    break;
    case f_behind:
        yaw = -90.0f;
        pitch = 0.0f;
        position = glm::vec3(translation[0], translation[1], translation[2] + size);
    break;
    case f_left:
        yaw = 360.0f;
        pitch = 0.0f;
        position = glm::vec3(translation[0] - size, translation[1], translation[2]);
    break;
    case f_right:
        yaw = 180.0f;
        pitch = 0.0f;
        position = glm::vec3(translation[0] + size, translation[1], translation[2]);
    break;
    case f_top:
    	yaw = 180.0f;
        pitch = -90.0f;
        position = glm::vec3(translation[0], translation[1] + size, translation[2]);
    break;
    case f_bottom:
        yaw = 360.0f;
        pitch = 90.0f;
        position = glm::vec3(translation[0], translation[1] - size, translation[2]);
    break;
    }
    
    if (firstFollowing) {
        Camera::get().updateCameraVectors();
    }
}

void Camera::neutralizeAngles() {
    pitch = 0.0f;
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 t_front;
    t_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    t_front.y = sin(glm::radians(pitch));
    t_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(t_front); 
    right = glm::normalize(glm::cross(front, worldUp));  
    up    = glm::normalize(glm::cross(right, front));
}
