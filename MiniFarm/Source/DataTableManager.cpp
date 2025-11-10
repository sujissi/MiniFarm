#include "PCH.h"
#include "DataTableManager.h"

std::unordered_map<int, CropData> DataTableManager::s_crops;
std::unordered_map<int, CropModelData> DataTableManager::s_cropModels;

void DataTableManager::Init()
{
    LoadCrops("Data/crops.csv");
    LoadCropModels("Data/crop_models.csv");
}

void DataTableManager::LoadCrops(const std::string& path)
{
    LOG("%s", path.c_str());
    std::ifstream file(path);
    std::string line; bool header = true;
    while (std::getline(file, line))
    {
        if (header) { header = false; continue; }
        std::stringstream ss(line); std::string cell;

        CropData d;
        std::getline(ss, cell, ','); d.id = static_cast<ECropID>(std::stoi(cell));
        std::getline(ss, cell, ','); d.name = cell;
        std::getline(ss, cell, ','); d.growTime = stof(cell);
        std::getline(ss, cell, ','); d.seedPrice = stoi(cell);
        std::getline(ss, cell, ','); d.sellPrice = stoi(cell);
        std::getline(ss, cell, ','); d.waterNeed = stoi(cell);

        s_crops[(int)d.id] = d;
    }
}

void DataTableManager::LoadCropModels(const std::string& path)
{
    LOG("%s", path.c_str());
    std::ifstream file(path);
    std::string line; bool header = true;
    while (std::getline(file, line))
    {
        if (header) { header = false; continue; }
        std::stringstream ss(line); std::string cell;

        ECropID id;
        CropModelData m;

        std::getline(ss, cell, ',');
        id = static_cast<ECropID>(std::stoi(cell));

        std::getline(ss, cell, ','); m.model0 = cell;
        std::getline(ss, cell, ','); m.model1 = cell;
        std::getline(ss, cell, ','); m.model2 = cell;
        std::getline(ss, cell, ','); m.model3 = cell;

        s_cropModels[(int)id] = m;
    }
}

const CropData* DataTableManager::GetCrop(ECropID  id) { return &s_crops[(int)id]; }
const CropModelData* DataTableManager::GetCropModel(ECropID  id) { return &s_cropModels[(int)id]; }
