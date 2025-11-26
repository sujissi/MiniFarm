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

	LoadStaticObjects("Data/static_props_pos.json");
	LoadInteractableObjects("Data/Interactable_props_pos.json");
}

void SceneManager::AddObject(std::shared_ptr<GameObject> obj)
{
	s_objects.push_back(obj);
}

void SceneManager::LoadStaticObjects(const std::string& path)
{
	std::string json = LoadFile(path);

	if (json.empty()) {
		LOG_E("Failed to load map file: %s", path.c_str());
		return;
	}

	rapidjson::Document doc;
	doc.Parse(json.c_str());

	if (!doc.IsObject() || !doc.HasMember("objects")) {
		LOG_E("Invalid map file: %s", path.c_str());
		return;
	}

	const auto& arr = doc["objects"].GetArray();

	auto readVec3 = [&](const rapidjson::Value& v)
		{
			return glm::vec3(
				v[0].GetFloat(),
				v[1].GetFloat(),
				v[2].GetFloat()
			);
		};

	for (auto& obj : arr)
	{
		std::string type = obj["type"].GetString();
		glm::vec3 pos = readVec3(obj["pos"]);
		glm::vec3 rot = readVec3(obj["rot"]);

		glm::vec3 scale(1.0);
		pos.x = -pos.x;
		rot.y = -rot.y;

		auto objInfo = DataTable::GetObjectInfo(type);
		if (!objInfo)
		{
			LOG_E("No object info for type: %s", type.c_str());
			continue;
		}
		auto inst = std::make_shared<StaticProp>(pos, rot, scale, objInfo->modelPath, objInfo->texturePath);
		if (inst)
		{
			inst->m_name = type;
			AddObject(inst);
			inst->Init();
		}
		else
			LOG_E("Unknown object type: %s", type.c_str());
	}
}

void SceneManager::LoadInteractableObjects(const std::string& path)
{
	std::string json = LoadFile(path);

	if (json.empty()) {
		LOG_E("Failed to load map file: %s", path.c_str());
		return;
	}

	rapidjson::Document doc;
	doc.Parse(json.c_str());

	if (!doc.IsObject() || !doc.HasMember("objects")) {
		LOG_E("Invalid map file: %s", path.c_str());
		return;
	}

	const auto& arr = doc["objects"].GetArray();

	auto readVec3 = [&](const rapidjson::Value& v)
		{
			return glm::vec3(
				v[0].GetFloat(),
				v[1].GetFloat(),
				v[2].GetFloat()
			);
		};

	for (auto& obj : arr)
	{
		std::string type = obj["type"].GetString();
		glm::vec3 pos = readVec3(obj["pos"]);
		glm::vec3 rot = readVec3(obj["rot"]);
		glm::vec3 scale = readVec3(obj["scale"]);
		pos.x = -pos.x;
		rot.y = -rot.y;

		auto objInfo = DataTable::GetObjectInfo(type);
		if (!objInfo)
		{
			LOG_E("No object info for type: %s", type.c_str());
			continue;
		}

		std::shared_ptr<GameObject> inst;
		if (type == "Field")
		{
			inst = std::make_shared<Crop>(pos, rot, scale, objInfo->modelPath, objInfo->texturePath);
		}
		else if (type == "House")
		{
			static int hcnt = 0;
			auto croptype = (hcnt == 0) ? EItemID::Carrot : EItemID::Cabbage;
			hcnt++;
			if (hcnt >= 2) LOG_E("");

			inst = std::make_shared<Shop>(pos, rot, scale, objInfo->modelPath, objInfo->texturePath);
			std::dynamic_pointer_cast<Shop>(inst)->SetCropType(croptype);
		}
		else if (type == "Boat")
		{
			inst = std::make_shared<Boat>(pos, rot, scale, objInfo->modelPath, objInfo->texturePath);
		}

		if (inst)
		{
			inst->m_name = type;
			AddObject(inst);
			inst->Init();
		}
		else
			LOG_E("Unknown object type: %s", type.c_str());
	}
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
	s_mainShader.Use();
	s_mainShader.SetView(s_camera.GetView());
	s_mainShader.SetProj(s_camera.GetProj((float)WINDOW_W / WINDOW_H));

	s_mainShader.SetLightPos(glm::vec3(10.f, 15.f, 10.f));
	s_mainShader.SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
	s_mainShader.SetViewPos(s_camera.eye);

	s_mainShader.SetModel(glm::mat4(1.0f));

	for (auto& obj : s_objects)
	{
		obj->DebugDraw();
		obj->Draw();
	}

	if (s_player->IsShopping())
	{
		DrawMessage("Buy[B]\nSell[S]\nExit[X]");
	}
	else if (s_player->HasInteractTarget())
	{
		TextRenderer::Draw("Press [E] to interact", WINDOW_W / 2, WINDOW_H / 2, 2, { 0,1,0.3 });

	}

	s_player->GetInventory().DrawUI();

	glutSwapBuffers();
}

void SceneManager::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void SceneManager::OnMouseClick(int x, int y)
{
	auto clickedObj = PickingSystem::PickObject(x, y);

	if (clickedObj && dynamic_cast<Player*>(clickedObj))
		return;

	if (clickedObj)
	{
		s_selected = clickedObj;
		LOG_D("Selected %s", clickedObj->m_name.c_str());
		return;
	}

	s_selected = nullptr;
	LOG_D("Selection cleared");
}

void SceneManager::DrawMessage(const std::string& msg)
{
	UIRenderer::DrawCenter(TextureLoader::Load("Assets/ui_board.png"), { 0.5f,0.5f }, 0.5f, { 1,1,1,0.5 });
	std::stringstream ss(msg);
	std::vector<std::string> lines;
	std::string line;

	while (std::getline(ss, line, '\n'))
		lines.push_back(line);

	float lineHeight = 30.f;

	float totalHeight = lineHeight * (lines.size() - 1);
	float startY = WINDOW_H / 2 - totalHeight * 0.5f;

	for (int i = 0; i < lines.size(); i++)
	{
		float y = startY + i * lineHeight;
		TextRenderer::Draw(lines[lines.size() - 1 - i], WINDOW_W / 2, y, 2, glm::vec4(0.f));
	}
}
