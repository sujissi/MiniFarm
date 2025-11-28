#include "PCH.h"
#include "IngameScene.h"
#include "SceneManager.h"
#include "UIRenderer.h"
#include "TextRenderer.h"
#include "ObjectLoader.h"
#include "Shader.h"
#include "DebugDrawer.h"

void IngameScene::Init()
{
	m_shader.Init("Shaders/main.vert", "Shaders/main.frag");
	DebugDrawer::Init(&m_shader);

	m_objects.clear();
	m_camera.Init();
	auto player = std::make_shared<Player>();
	m_player = player.get();
	AddObject(player);

	auto staticObjs = ObjectLoader::LoadStaticObjects("Data/static_props_pos.json");
	auto interactObjs = ObjectLoader::LoadInteractableObjects("Data/Interactable_props_pos.json");

	for (auto& obj : staticObjs)
		AddObject(obj);

	for (auto& obj : interactObjs)
		AddObject(obj);
}

void IngameScene::Update(int dt)
{
	for (auto& obj : m_objects)
	{
		obj->Update(dt);
	}
	glutPostRedisplay();
	glutTimerFunc(FRAME_TIME_MS, SceneManager::Update, 0);
}

void IngameScene::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetupCameraAndLight();
	DrawWorld();
	DrawUI();
	glutSwapBuffers();

}

void IngameScene::DrawWorld()
{
	for (auto& obj : m_objects)
	{
		obj->DebugDraw();
		obj->Draw();
	}
}

void IngameScene::DrawUI()
{
	if (m_player->IsShopping() || m_player->IsEscaping())
	{
		UIRenderer::DrawMessage(m_player->GetSysMsg());
	}
	else if (m_player->HasInteractTarget())
	{
		UIRenderer::DrawCenter(TextureLoader::Load("Assets/ui_board_black_thin.png"), { 0.5f,0.6f }, 0.6f, { 1,1,1,0.6 });
		TextRenderer::Draw("Press [E] to interact", WINDOW_W / 2, WINDOW_H / 2 + 50, 2, { 0,1,0.2 });
	}

	m_player->GetInventory().DrawUI();
}

void IngameScene::SetupCameraAndLight()
{
	m_shader.Use();
	m_shader.SetView(m_camera.GetView());
	m_shader.SetProj(m_camera.GetProj((float)WINDOW_W / WINDOW_H));

	m_shader.SetLightPos(glm::vec3(10.f, 15.f, 10.f));
	m_shader.SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
	m_shader.SetViewPos(m_camera.eye);

	m_shader.SetModel(glm::mat4(1.0f));
}
