#include "PCH.h"
#include "Crop.h"
#include "DataTable.h"
#include "Model.h"
#include "Player.h"
#include "UIRenderer.h"
#include "TextureLoader.h"
#include "SceneManager.h"

Crop::Crop(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale,
	const std::string& model, const std::string& texture)
	: InteractableObject(pos, rot, scale)
{
	m_level = 0;
	m_water = 0.f;
	m_id = EItemID::Empty;

	m_model = ModelCache::Get(model, texture);
}

void Crop::SetCropState(EItemID newID, int newLevel)
{
	m_id = newID;
	m_level = newLevel;
	m_water = 0.f;

	const CropData* data = DataTable::GetCrop(m_id);
	if (!data || data->stageTypes.empty())
		return;

	const std::string& typeName = data->stageTypes[m_level];
	const ObjectInfo* info = DataTable::GetObjectInfo(typeName);

	if (info)
		m_model = ModelCache::Get(info->modelPath, info->texturePath);
}

void Crop::Update(int dt)
{
	if (!m_model) return;

	if (m_id == EItemID::Empty || m_id == EItemID::Tilled)
		return;

	const CropData* data = DataTable::GetCrop(m_id);
	if (!data) return;

	int maxLevel = (int)data->stageTypes.size() - 1;
	if (m_level >= maxLevel)
		return;

	float requiredWater = data->waterStages[m_level];

	if (m_water >= requiredWater)
	{
		m_water -= requiredWater;
		m_level++;

		const std::string& typeName = data->stageTypes[m_level];
		const ObjectInfo* info = DataTable::GetObjectInfo(typeName);

		if (info)
			m_model = ModelCache::Get(info->modelPath, info->texturePath);

		LOG_D("Crop grew to level %d (used %.1f water)", m_level, requiredWater);
	}

	if (m_water < 0.f)
		m_water = 0.f;
}


void Crop::AddWater(float amount)
{
	m_water += amount;
}

void Crop::OnInteract(Player* player)
{
	auto tool = static_cast<EItemID>(player->GetEquippedTool());

	switch (tool)
	{
	case EItemID::Hoe:
	{
		if (m_id == EItemID::Empty)
		{
			SetCropState(EItemID::Tilled, 0);
			LOG_D("Soil tilled");
		}
		break;
	}
	case EItemID::SeedCarrot:
	{
		if (m_id == EItemID::Tilled)
		{
			if (!player->UseItem(tool)) break;
			SetCropState(EItemID::Carrot, 0);
			LOG_D("Carrot planted");
		}
		break;
	}
	case EItemID::SeedCabbage:
	{
		if (m_id == EItemID::Tilled)
		{
			if (!player->UseItem(tool)) break;
			SetCropState(EItemID::Cabbage, 0);
			LOG_D("Cabbage planted");
		}
		break;
	}
	case EItemID::WateringCan:
	{
		if (m_id != EItemID::Empty && m_id != EItemID::Tilled)
		{
			AddWater(5.f);
			LOG_D("Crop watered. Current water: %.2f", m_water);
		}
		break;
	}
	case EItemID::Sickle:
	{
		const CropData* data = DataTable::GetCrop(m_id);

		if (data && m_level == (int)data->stageTypes.size() - 1)
		{
			player->AddItem(m_id);
			SetCropState(EItemID::Tilled, 0);
			LOG_D("Crop harvested");
		}
		break;
	}
	default:
		break;
	}
}

float Crop::GetGrowProgress() const
{
	const CropData* data = DataTable::GetCrop(m_id);
	if (!data) return 0.f;

	if (m_level >= (int)data->stageTypes.size() - 1)
		return 1.f;

	float requiredWater = data->waterStages[m_level];

	if (requiredWater <= 0) return 0.f;

	return glm::clamp(m_water / requiredWater, 0.f, 1.f);
}


void Crop::DrawBar()
{
	if (m_id == EItemID::Empty || m_id == EItemID::Tilled)
		return;

	float progress = GetGrowProgress();

	glm::vec3 worldPos = m_pos + glm::vec3(0, 3.0f, 0);

	glm::mat4 view = SceneManager::GetCamera().GetView();
	glm::mat4 proj = SceneManager::GetCamera().GetProj(WINDOW_W / (float)WINDOW_H);

	glm::vec4 clip = proj * view * glm::vec4(worldPos, 1.0f);
	glm::vec3 ndc = glm::vec3(clip) / clip.w;

	glm::vec2 uiPos = {
		ndc.x * 0.5f + 0.5f,
		ndc.y * 0.5f + 0.5f
	};
	glm::vec2 fillPos = uiPos - glm::vec2(0.05f, 0.0f);

	TextureInfo bg = TextureLoader::Load("Assets/ui_bar_bg.png");
	UIRenderer::Draw(bg, fillPos, 0.1f, { 1,1,1,1 });

	TextureInfo fill = (m_id == EItemID::Carrot)
		? TextureLoader::Load("Assets/ui_bar_carrot.png")
		: TextureLoader::Load("Assets/ui_bar_cabbage.png");
	UIRenderer::DrawFill(fill, fillPos, 0.1f, progress, { 1,1,1,1 });
}
