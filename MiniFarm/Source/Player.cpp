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
}

void Player::Update(int time)
{
	auto& cam = SceneManager::GetCamera();
	cam.at = Player::m_pos;
	if (InputManager::IsKeyDown('w')) {
		Player::m_pos.z -= 0.1f;
		glm::abs(Player::m_pos.z);
		cam.MoveForward(-0.1f);
		glm::abs(cam.eye.z);
		LOG("%f, %f, %f", Player::m_pos.x, Player::m_pos.y, Player::m_pos.z);
	}
	if (InputManager::IsKeyDown('s')) {
		Player::m_pos.z += 0.1f;
		glm::abs(Player::m_pos.z);
		cam.MoveForward(0.1f);
		glm::abs(cam.eye.z);
		LOG("%f, %f, %f", Player::m_pos.x, Player::m_pos.y, Player::m_pos.z);
	}
	if (InputManager::IsKeyDown('a')) {
		Player::m_pos.x -= 0.1f;
		glm::abs(Player::m_pos.x);
		cam.MoveRight(-0.1f);
		glm::abs(cam.eye.x);
		LOG("%f, %f, %f", Player::m_pos.x, Player::m_pos.y, Player::m_pos.z);
	}
	if (InputManager::IsKeyDown('d')) {
		Player::m_pos.x += 0.1f;
		glm::abs(Player::m_pos.x);
		cam.MoveRight(0.1f);
		glm::abs(cam.eye.x);
		LOG("%f, %f, %f", Player::m_pos.x, Player::m_pos.y, Player::m_pos.z);
	}
}