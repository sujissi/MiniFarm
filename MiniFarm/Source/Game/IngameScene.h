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
	void AddObject(std::shared_ptr<GameObject> obj)
	{
		m_objects.push_back(obj);
	}

private:
	Player* m_player;
};
