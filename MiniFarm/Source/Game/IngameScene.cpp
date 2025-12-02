#include "PCH.h"
#include "IngameScene.h"
#include "SceneManager.h"
#include "UIRenderer.h"
#include "TextRenderer.h"
#include "ObjectLoader.h"
#include "Shader.h"

void IngameScene::Init()
{
	SetClearColor(glm::vec3(1, 1, 1));

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
	m_timeSystem.Update(dt);
	UpdateDayNightCycle();
	SetClearColor(m_BackGroundColor);
}

void IngameScene::Draw()
{
	SetupCameraAndLight();
	DrawWorld();
	DrawUI();
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

	float timeValue = m_timeSystem.GetDayTime();
	int hour = (int)timeValue;                          
	int minute = (int)((timeValue - hour) * 60.f);      
	int second = (int)((((timeValue - hour) * 60.f) - minute) * 60.f); 
	UIRenderer::DrawCenter(TextureLoader::Load("Assets/ui_board_black_thin.png"), { 0.5f,0.9f }, 0.3f, { 1,1,1,0.6 });
	TextRenderer::Draw(std::format("{:02d}:{:02d}:{:02d}", hour, minute, second), WINDOW_W / 2, WINDOW_H - 50, 2.0f, { 1,1,1 });
}

void IngameScene::SetupCameraAndLight()
{
	Shader* shader = &SceneManager::GetMainShader();
	shader->Use();
	shader->SetView(m_camera.GetView());
	shader->SetProj(m_camera.GetProj((float)WINDOW_W / WINDOW_H));
	
	shader->SetLightPos(m_lightPos);
	shader->SetLightColor(m_lightColor);
	shader->SetViewPos(m_camera.eye);
	
	shader->SetModel(glm::mat4(1.0f));
}

void IngameScene::UpdateDayNightCycle()
{
	float dayTime = m_timeSystem.GetDayTime();
	const float DAY_START = 6.f;
	const float DAY_END = 18.f;

	if (m_timeSystem.IsDaytime())
	{
		float dayProgress = m_timeSystem.GetDayProgress();
		float angle = dayProgress * 3.14159265f;
		
		m_lightPos.x = -LIGHT_WIDTH / 2.f + dayProgress * LIGHT_WIDTH;
		m_lightPos.y = sin(angle) * LIGHT_HEIGHT;
		
		if (dayProgress < 0.1f)
		{
			float t = dayProgress / 0.1f;
			m_lightColor = glm::mix(glm::vec3(0.8f, 0.5f, 0.3f), glm::vec3(1.f, 1.f, 0.9f), t);
			m_BackGroundColor = glm::mix(glm::vec3(0.2f, 0.2f, 0.4f), glm::vec3(0.5f, 0.7f, 1.f), t);
		}
		else if (dayProgress > 0.9f) 
		{
			float t = (dayProgress - 0.9f) / 0.1f;
			m_lightColor = glm::mix(glm::vec3(1.f, 1.f, 0.9f), glm::vec3(1.f, 0.6f, 0.3f), t);
			m_BackGroundColor = glm::mix(glm::vec3(0.5f, 0.7f, 1.f), glm::vec3(0.2f, 0.2f, 0.4f), t);
		}
		else
		{
			m_lightColor = glm::vec3(1.f, 1.f, 0.9f);
			m_BackGroundColor = glm::vec3(0.5f, 0.8f, 1.f);
		}
	}
	else
	{
		m_lightPos.x = 0.f;
		m_lightPos.y = LIGHT_HEIGHT * 0.6f;
		
		if (dayTime >= DAY_END && dayTime < DAY_END + 1.f)
		{
			float t = (dayTime - DAY_END);
			m_lightColor = glm::mix(glm::vec3(1.f, 0.6f, 0.3f), glm::vec3(0.2f, 0.2f, 0.4f), t);
			m_BackGroundColor = glm::mix(glm::vec3(0.5f, 0.7f, 1.f), glm::vec3(0.1f, 0.1f, 0.2f), t);
		}
		else if (dayTime >= DAY_START - 1.f && dayTime < DAY_START)
		{
			float t = (dayTime - (DAY_START - 1.f));
			m_lightColor = glm::mix(glm::vec3(0.2f, 0.2f, 0.4f), glm::vec3(0.8f, 0.5f, 0.3f), t);
			m_BackGroundColor = glm::mix(glm::vec3(0.2f, 0.2f, 0.4f), glm::vec3(0.5f, 0.7f, 1.f), t);
		}
		else
		{
			m_lightColor = glm::vec3(0.2f, 0.2f, 0.4f);
			m_BackGroundColor = glm::vec3(0.1f, 0.1f, 0.2f);
		}
	}
}