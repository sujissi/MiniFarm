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

    m_inventory.AddItem(EItemID::Hoe, 1);
    m_inventory.AddItem(EItemID::WateringCan, 1);
    m_inventory.AddItem(EItemID::Sickle, 1);
}

void Player::Update(int time)
{
    HandleMouseInput();
    HandleKeyInput();
}

void Player::HandleMouseInput()
{
    auto& cam = SceneManager::GetCamera();

    float rotSpeed = 0.2f;
    cam.AddYaw(InputManager::GetDeltaX() * rotSpeed);
    cam.AddPitch(-InputManager::GetDeltaY() * rotSpeed);

    m_rot.y = cam.GetFlatYaw();

    InputManager::ResetDelta();
}

void Player::HandleKeyInput()
{
    auto& cam = SceneManager::GetCamera();

    glm::vec3 forward = cam.GetForwardFlat();
    glm::vec3 right = cam.GetRightFlat();

    glm::vec3 move(0);

    if (InputManager::IsKeyDown('w')) move += forward;
    if (InputManager::IsKeyDown('s')) move -= forward;
    if (InputManager::IsKeyDown('a')) move -= right;
    if (InputManager::IsKeyDown('d')) move += right;

    if (glm::length(move) > 0)
        m_pos += glm::normalize(move) * m_speed;

    cam.FollowTarget(m_pos);
}
