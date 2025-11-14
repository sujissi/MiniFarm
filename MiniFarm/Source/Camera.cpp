#include "PCH.h"
#include "Camera.h"

Camera::Camera()
{
	Init();
}

void Camera::Init()
{
	eye = { 0.0f, 6.0f, 10.0f };
	at = { 0.0f, 0.0f, 0.0f };
	up = { 0.0f, 1.0f, 0.0f };

	yaw = 0.f;
	pitch = 20.f;
	distance = 10.f;
}

glm::vec3 Camera::GetForward() const
{
	return glm::normalize(at - eye);
}

void Camera::AddYaw(float delta)
{
	yaw += delta;
}

void Camera::AddPitch(float delta)
{
	pitch += delta;
	pitch = glm::clamp(pitch, 20.0f, 30.0f);
}

void Camera::FollowTarget(const glm::vec3& targetPos)
{
    at = targetPos;

    float yawRad = glm::radians(yaw);
    float pitchRad = glm::radians(pitch);

    float h = cos(pitchRad) * distance;
    float v = sin(pitchRad) * distance;

	eye.x = at.x - h * sin(yawRad);
	eye.y = at.y + v;
	eye.z = at.z + h * cos(yawRad);
}


glm::mat4 Camera::GetView() const
{
	return glm::lookAt(eye, at, up);
}

glm::mat4 Camera::GetProj(float aspect) const
{
	return glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.f);
}