#include "PCH.h"
#include "DataTableManager.h"

std::unordered_map<int, CropData> DataTableManager::s_crops;

void DataTableManager::Init()
{
    LoadCrops("Data/crops.csv");
}

void DataTableManager::LoadCrops(const std::string& path)
{
    std::ifstream file(path);
    std::string line;

    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        CropData data;
        std::string token;

        std::getline(ss, token, ','); data.id = static_cast<ECropID>(std::stoi(token));
        std::getline(ss, data.name, ',');
        std::getline(ss, token, ','); data.seedPrice = std::stoi(token);
        std::getline(ss, token, ','); data.sellPrice = std::stoi(token);

        for (int i = 0; i < 4; i++)
        {
            std::getline(ss, data.levels[i].model, ',');
            std::getline(ss, token, ','); data.levels[i].waterRequired = std::stof(token);
            std::getline(ss, token, ','); data.levels[i].timeRequired = std::stof(token);
        }

        s_crops[(int)data.id] = data;
    }
}

const CropData* DataTableManager::GetCrop(ECropID  id) { return &s_crops[(int)id]; }
