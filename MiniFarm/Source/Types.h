#pragma once

using ItemID = int;

enum class ECropID : ItemID
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

enum class EToolID : ItemID
{
    // Tools
    Hoe = 3,
    WateringCan,
    Sickle,

    // Seeds
    SeedCarrot,
    SeedCabbage,
};
