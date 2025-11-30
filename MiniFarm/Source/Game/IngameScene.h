#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Player.h"
#include "Shader.h"

class IngameScene : public Scene
{
public:
	void Init() override;
	void Update(int dt) override;
	void Draw() override;

	void DrawWorld();
	void DrawUI();
	void SetupCameraAndLight();

private:
	Player* m_player;
};
