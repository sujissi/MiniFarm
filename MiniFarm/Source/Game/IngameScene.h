#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Player.h"
#include "Shader.h"
#include "TimeSystem.h"

class IngameScene : public Scene
{
public:
	void Init() override;
	void Update(int dt) override;
	void Draw() override;

	void DrawWorld();
	void DrawUI();
	void SetupCameraAndLight();
	void UpdateDayNightCycle();

private:
	Player* m_player;
	TimeSystem m_timeSystem;
	
	const float LIGHT_WIDTH = 20.f;
	const float LIGHT_HEIGHT = 20.f;
	glm::vec3 m_BackGroundColor = glm::vec3(1.f,1.f,1.f);
	glm::vec3 m_lightPos = glm::vec3(-15.f, 0.f, 0.f);
	glm::vec3 m_lightColor = glm::vec3(1.f, 1.f, 1.f);
};
