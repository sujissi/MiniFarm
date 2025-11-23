#include "PCH.h"
#include "Crop.h"
#include "DataTable.h"
#include "Model.h"

Crop::Crop(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale,
	const std::string& model, const std::string& texture)
	: InteractableObject(pos, rot, scale)
{
	m_level = 0;
	m_time = 0.f;
	m_water = 0.f;
	m_id = ECropID::Empty;

	m_model = ModelCache::Get(model, texture);
}


void Crop::Update(int dt)
{
	if (!m_model)
	{
		LOG_E("");
		return;
	}

	if (m_id == ECropID::Empty || m_id == ECropID::Tilled)
		return;

	const auto* data = DataTable::GetCrop(m_id);
	const auto& info = data->levels[m_level];

	if (m_water < info.waterRequired)
		return;

	m_time += dt * 0.001f;
	bool bLevelUp = (m_time >= info.timeRequired) && (m_level < 3);
	if (bLevelUp)
	{
		m_time = 0.f;
		m_level++;
		m_model = std::make_shared<Model>(data->levels[m_level].model);
	}

	m_water -= dt * 0.001f;
	if (m_water < 0.f) m_water = 0.f;
}

void Crop::AddWater(float amount)
{
	m_water += amount;
}

void Crop::Interact(Player* player)
{
}
