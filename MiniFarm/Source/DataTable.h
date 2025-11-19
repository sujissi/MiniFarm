#pragma once
#include "GameTypes.h"

class DataTable
{
public:
    static void Init();
    static const CropData* GetCrop(ECropID  id);

private:
    static void LoadCrops(const std::string& path);
    static std::unordered_map<int, CropData> s_crops;
};
