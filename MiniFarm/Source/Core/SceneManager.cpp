#include "PCH.h"
#include "SceneManager.h"
#include "Shader.h"
#include "PickingSystem.h"
#include <rapidjson/document.h>
#include "DataTable.h"
#include "StaticProp.h"
#include "Crop.h"
#include "Shop.h"
#include "Boat.h"
#include "DebugDrawer.h"
#include "UIRenderer.h"
#include "TextureLoader.h"
#include "TextRenderer.h"
#include "ObjectLoader.h"

std::vector<std::shared_ptr<GameObject>> SceneManager::s_objects;
Camera SceneManager::s_camera;
GameObject* SceneManager::s_selected = nullptr;
Shader SceneManager::s_mainShader;
Player* SceneManager::s_player = nullptr;

void SceneManager::Init()
{
	s_mainShader.Init("Shaders/main.vert", "Shaders/main.frag");
	DebugDrawer::Init(&s_mainShader);
	TextRenderer::Init();
	UIRenderer::Init();
	DataTable::Init();
	s_objects.clear();
	s_camera.Init();
	auto player = std::make_shared<Player>();
	s_player = player.get();
	AddObject(player);

	ObjectLoader::LoadStaticObjects("Data/static_props_pos.json");
	ObjectLoader::LoadInteractableObjects("Data/Interactable_props_pos.json");
}

void SceneManager::AddObject(std::shared_ptr<GameObject> obj)
{
	s_objects.push_back(obj);
}

void SceneManager::Update(int time)
{
	for (auto& obj : s_objects)
	{
		obj->Update(time);
	}
	glutPostRedisplay();
	glutTimerFunc(FRAME_TIME_MS, SceneManager::Update, 0);
}

void SceneManager::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupCameraAndLight();
	DrawWorld();
	DrawUI();

	glutSwapBuffers();
}

void SceneManager::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void SceneManager::DrawWorld()
{
	for (auto& obj : s_objects)
	{
		obj->DebugDraw();
		obj->Draw();
	}
}

void SceneManager::DrawUI()
{
	if (s_player->IsShopping() || s_player->IsEscaping())
	{
		UIRenderer::DrawMessage(s_player->GetSysMsg());
	}
	else if (s_player->HasInteractTarget())
	{
		UIRenderer::DrawCenter(TextureLoader::Load("Assets/ui_board_black_thin.png"), { 0.5f,0.6f }, 0.6f, { 1,1,1,0.6 });
		TextRenderer::Draw("Press [E] to interact", WINDOW_W / 2, WINDOW_H / 2 + 50, 2, { 0,1,0.2 });
	}

	s_player->GetInventory().DrawUI();
}

void SceneManager::SetupCameraAndLight()
{
	s_mainShader.Use();
	s_mainShader.SetView(s_camera.GetView());
	s_mainShader.SetProj(s_camera.GetProj((float)WINDOW_W / WINDOW_H));

	s_mainShader.SetLightPos(glm::vec3(10.f, 15.f, 10.f));
	s_mainShader.SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
	s_mainShader.SetViewPos(s_camera.eye);

	s_mainShader.SetModel(glm::mat4(1.0f));
}

