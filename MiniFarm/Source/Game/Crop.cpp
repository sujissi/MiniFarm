#include "PCH.h"
#include "Crop.h"
#include "DataTable.h"
#include "Model.h"
#include "Player.h"

Crop::Crop(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale,
	const std::string& model, const std::string& texture)
	: InteractableObject(pos, rot, scale)
{
	m_level = 0;
	m_time = 0.f;
	m_water = 0.f;
	m_id = EItemID::Empty;

	m_model = ModelCache::Get(model, texture);
}

void Crop::SetCropState(EItemID newID, int newLevel)
{
    m_id = newID;
    m_level = newLevel;
    m_time = 0.f;
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
	if (!m_model)
	{
		LOG_E("Crop model missing");
		return;
	}

	if (m_id == EItemID::Empty || m_id == EItemID::Tilled)
		return;

	const auto* data = DataTable::GetCrop(m_id);
	if (!data) return;

	if (m_water <= 0.f)
		return;

	m_time += dt * 0.001f;
	bool canLevelUp = (m_time >= 5.f) && (m_level < (int)data->stageTypes.size() - 1);

	if (canLevelUp)
	{
		m_time = 0.f;
		m_level++;

		const std::string& typeName = data->stageTypes[m_level];
		const ObjectInfo* info = DataTable::GetObjectInfo(typeName);

		if (info)
			m_model = ModelCache::Get(info->modelPath, info->texturePath);

		LOG_D("Crop grew to level %d", m_level);
	}

	m_water -= dt * 0.001f;
	if (m_water < 0.f) m_water = 0.f;
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
            SetCropState(EItemID::Carrot, 0);
            LOG_D("Carrot planted");
        }
        break;
    }
    case EItemID::SeedCabbage:
    {
        if (m_id == EItemID::Tilled)
        {
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
            // TODO: player->AddItem(m_id);
            SetCropState(EItemID::Tilled, 0);
            LOG_D("Crop harvested");
        }
        break;
    }
    default:
        break;
    }
}

