#include "PCH.H"
#include "Player.h"
#include "SceneManager.h"
#include "InputManager.h"

Player::Player()
{
	m_model = std::make_shared<Model>("Models/cube.obj");
	m_pos = { 0.f, 0.f, 0.f };
	m_rot = { 0.f, 0.f, 0.f };
	m_scale = { 1.f, 1.f, 1.f };
    m_speed = 0.1f;
}

void Player::Update(int time)
{
    auto& cam = SceneManager::GetCamera();

    float rotSpeed = 0.2f;
    float dx = static_cast<float>(InputManager::GetDeltaX());
    float dy = static_cast<float>(InputManager::GetDeltaY());

    cam.AddYaw(dx * rotSpeed);
    cam.AddPitch(-dy * rotSpeed);

    glm::vec3 camForward = cam.GetForward();

    glm::vec3 forward = glm::normalize(glm::vec3(camForward.x, 0.0f, camForward.z));
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
    float yawRad = std::atan2(forward.x, forward.z);
    m_rot.y = glm::degrees(yawRad);

    glm::vec3 move(0);

    if (InputManager::IsKeyDown('w')) move += forward;
    if (InputManager::IsKeyDown('s')) move -= forward;
    if (InputManager::IsKeyDown('a')) move -= right;
    if (InputManager::IsKeyDown('d')) move += right;

    if (glm::length(move) > 0)
        m_pos += glm::normalize(move) * m_speed;

    cam.FollowTarget(m_pos);

    InputManager::ResetDelta();
}
