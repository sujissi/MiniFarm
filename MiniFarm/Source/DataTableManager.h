#pragma once

enum class ECropID
{
    Carrot = 1,
    Cabbage = 2
};

struct CropData
{
    ECropID id;
    std::string name;
    float growTime;
    int seedPrice;
    int sellPrice;
    int waterNeed;
};

struct CropModelData
{
    std::string model0;
    std::string model1;
    std::string model2;
    std::string model3;
};

class DataTableManager
{
public:
    static void Init();

    static const CropData* GetCrop(ECropID  id);
    static const CropModelData* GetCropModel(ECropID  id);

private:
    static void LoadCrops(const std::string& path);
    static void LoadCropModels(const std::string& path);

    static std::unordered_map<int, CropData> s_crops;
    static std::unordered_map<int, CropModelData> s_cropModels;
};
