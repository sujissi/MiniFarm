#include "PCH.h"
#include "TitleScene.h"
#include "TextRenderer.h"
#include "SceneManager.h"
#include "IngameScene.h"
#include "InputManager.h"
#include "ObjectLoader.h"

void TitleScene::Init()
{
	SetClearColor(glm::vec3(1, 1, 1));

	m_shader.Init("Shaders/main.vert", "Shaders/main.frag");
	m_objects.clear();

	m_camera.yaw = 30.0f;
	m_camera.pitch = 20.0f;
	m_camera.distance = 60.0f;
	m_camera.FollowTarget(glm::vec3(0.f));

	auto staticObjs = ObjectLoader::LoadStaticObjects("Data/static_props_pos.json");
	auto interactObjs = ObjectLoader::LoadInteractableObjects("Data/Interactable_props_pos.json");

	for (auto& obj : staticObjs)
		AddObject(obj);

	for (auto& obj : interactObjs)
		AddObject(obj);
}

void TitleScene::Update(int dt)
{
	if (InputManager::IsKeyPressed('\r')) // Enter
	{
		SceneManager::SetScene(std::make_unique<IngameScene>());
	}

	m_camera.AddYaw(0.01f * dt);
	m_camera.FollowTarget(glm::vec3(0.f));
}

void TitleScene::Draw()
{
	SetupCameraAndLight();
	DrawWorld();

	TextRenderer::Draw("MiniFarm", WINDOW_W / 2, WINDOW_H / 2 + 20, 5, { 1,1,0 });
	TextRenderer::Draw("Press [Enter] to start", WINDOW_W / 2, WINDOW_H / 2 - 60, 2, { 1,1,1 });
}

void TitleScene::DrawWorld()
{
	for (auto& obj : m_objects)
	{
		obj->DebugDraw();
		obj->Draw();
	}
}

void TitleScene::SetupCameraAndLight()
{
	m_shader.Use();
	m_shader.SetView(m_camera.GetView());
	m_shader.SetProj(m_camera.GetProj((float)WINDOW_W / WINDOW_H));

	m_shader.SetLightPos(glm::vec3(10.f, 15.f, 10.f));
	m_shader.SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
	m_shader.SetViewPos(m_camera.eye);

	m_shader.SetModel(glm::mat4(1.0f));
}
