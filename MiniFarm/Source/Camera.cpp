#include "PCH.h"
#include "Camera.h"

Camera::Camera()
{
    Init();
}

void Camera::Init()
{
    eye = { 0.0f, 1.5f, 5.0f };
    at = { 0.0f, 0.0f, 0.0f };
    up = { 0.0f, 1.0f, 0.0f };
}

void Camera::MoveForward(float amount)
{
    LOG("");
    glm::vec3 dir = glm::normalize(at - eye);
    eye += dir * amount;
    at += dir * amount;
}

void Camera::MoveRight(float amount)
{
    LOG("");
    glm::vec3 dir = glm::normalize(at - eye);
    glm::vec3 right = glm::normalize(glm::cross(dir, up));
    eye += right * amount;
    at += right * amount;
}

void Camera::RotateYaw(float deg)
{
    LOG("");
    float rad = glm::radians(deg);
    glm::vec3 dir = at - eye;
    float nx = dir.x * cos(rad) - dir.z * sin(rad);
    float nz = dir.x * sin(rad) + dir.z * cos(rad);
    at = eye + glm::vec3(nx, dir.y, nz);
}

glm::mat4 Camera::GetView() const
{
    return glm::lookAt(eye, at, up);
}

glm::mat4 Camera::GetProj(float aspect) const
{
    return glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.f);
}
