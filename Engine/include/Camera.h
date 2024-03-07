#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>



class Camera {
public:
    enum class CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    Camera();
    ~Camera();

    void setPerspective(float fov, float aspect, float near, float far);
    void setOrthographic(float left, float right, float bottom, float top, float near, float far);

    void setPosition(const glm::vec3& position);
    void setRotation(float yaw, float pitch, float roll);
    void setTarget(const glm::vec3& target);

    void move(float deltaTime);
    void rotate(float deltaX, float deltaY);

    const glm::mat4& getViewMatrix() const;
    const glm::mat4& getProjectionMatrix() const;

    glm::vec3 getPosition();


private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 target;  // New member representing the camera's target

    float yaw;
    float pitch;
    float roll;

    float movementSpeed;
    float rotationSpeed;

    void updateViewMatrix();
};