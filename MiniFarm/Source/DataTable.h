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
    int seedPrice;
    int sellPrice;

    struct LevelInfo
    {
        std::string model;
        float waterRequired;
        float timeRequired;
    };

    LevelInfo levels[4];
};


class DataTable
{
public:
    static void Init();

    static const CropData* GetCrop(ECropID  id);

private:
    static void LoadCrops(const std::string& path);

    static std::unordered_map<int, CropData> s_crops;
};
