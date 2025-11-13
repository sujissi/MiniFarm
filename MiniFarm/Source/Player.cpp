#include "PCH.H"
#include "Player.h"
#include "SceneManager.h"
#include "InputManager.h"

// 플레이어 생성자
Player::Player()
{
	// 플레이어 모델 로드
	m_model = std::make_shared<Model>("Models/cube.obj");
	// 플레이어 위치
	m_pos = { 0.f, 0.f, 0.f };
	// 플레이어 방향 조절
	m_rot = { 0.f, 0.f, 0.f }; // (x각도, y각도, z각도)
	// 플레이어 크기 조절
	m_scale = { 1.f, 1.f, 1.f };
	// 이동 속도 설정
	speed = 0.1f;
}

// 플레이어 업데이트 함수
void Player::Update(int time)
{
	// 카메라 참조
	auto &cam = SceneManager::GetCamera();
	// 위쪽 이동
	if (InputManager::IsKeyDown('w')) {
		m_pos.z -= speed;
		cam.eye.z -= speed;
		glm::abs(m_pos.z);
		glm::abs(cam.eye.z);
		LOG("%f, %f, %f", Player::m_pos.x, Player::m_pos.y, Player::m_pos.z);
	}
	// 아래쪽 이동
	if (InputManager::IsKeyDown('s')) {
		m_pos.z += speed;
		cam.eye.z += speed;
		glm::abs(m_pos.z);
		glm::abs(cam.eye.z);
		LOG("%f, %f, %f", Player::m_pos.x, Player::m_pos.y, Player::m_pos.z);
	}
	// 왼쪽 이동
	if (InputManager::IsKeyDown('a')) {
		m_pos.x -= speed;
		cam.eye.x -= speed;
		glm::abs(m_pos.x);
		glm::abs(cam.eye.x);
		LOG("%f, %f, %f", Player::m_pos.x, Player::m_pos.y, Player::m_pos.z);
	}
	// 오른쪽 이동
	if (InputManager::IsKeyDown('d')) {
		m_pos.x += speed;
		cam.eye.x += speed;
		glm::abs(m_pos.x);
		glm::abs(cam.eye.x);
		LOG("%f, %f, %f", Player::m_pos.x, Player::m_pos.y, Player::m_pos.z);
	}
	// 카메라 바라보는 방향 동기화
	cam.at = Player::m_pos;
}