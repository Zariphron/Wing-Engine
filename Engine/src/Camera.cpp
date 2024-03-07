#include "camera.h"

Camera::Camera() {
    // Initialize camera parameters
    position = glm::vec3(2.0f, 2.0f, 2.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::cross(front, up);
    target = glm::vec3(0.0f, 0.0f, 0.0f);  // Initialize the target to the origin
    yaw = -90.0f;
    pitch = 0.0f;
    roll = 0.0f;
    movementSpeed = 2.5f;
    rotationSpeed = 0.1f;
    updateViewMatrix();
}

Camera::~Camera() {}

void Camera::setPerspective(float fov, float aspect, float near, float far) {
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
}

void Camera::setOrthographic(float left, float right, float bottom, float top, float near, float far) {
    projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
}

void Camera::setPosition(const glm::vec3& position) {
    this->position = position;
    updateViewMatrix();
}

void Camera::setRotation(float yaw, float pitch, float roll) {
    this->yaw = yaw;
    this->pitch = pitch;
    this->roll = roll;
    updateViewMatrix();
}

void Camera::setTarget(const glm::vec3& target) {
    this->target = target;
    updateViewMatrix();
}

void Camera::move(float deltaTime) {
    // Handle user input for camera movement (e.g., WASD keys)
    // Update the position based on input and deltaTime
    // ...

    updateViewMatrix();
}

void Camera::rotate(float deltaX, float deltaY) {
    // Update yaw and pitch based on mouse movement
    yaw += deltaX * rotationSpeed;
    pitch += deltaY * rotationSpeed;

    // Clamp pitch to avoid gimbal lock
    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    // Update the view matrix
    updateViewMatrix();
}

const glm::mat4& Camera::getViewMatrix() const {
    return viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

void Camera::updateViewMatrix() {
    front = glm::normalize(target - position);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));

    viewMatrix = glm::lookAt(position, target, up);
}

glm::vec3 Camera::getPosition() {
    return position;
}
