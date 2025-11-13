#include "PCH.h"
#include "Crop.h"
#include "DataTableManager.h"
#include "Model.h"

Crop::Crop(ECropID id)
    : m_id(id)
{
    const auto* data = DataTableManager::GetCrop(id);

    m_level = 0;
    m_time = 0.f;
    m_water = 0.f;

    m_model = std::make_shared<Model>(data->levels[0].model);// TDDO: empty ground obj
    m_scale = { 1,1,1 };
}


void Crop::Update(int dt)
{
    if (!m_model)
    {
        LOG_E("");
        return;
    }

    const auto* data = DataTableManager::GetCrop(m_id);
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
