#pragma once

using ItemID = int;

enum class ECropID : ItemID
{
    Empty = -1, // ∞•¡ˆ æ ¿∫ ∂•
    Tilled = 0, // ∞•æ∆≥ı¿∫ ∂•
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
    None = -1,
    // Tools
    Hoe = 3,
    WateringCan,
    Sickle,

    // Seeds
    SeedCarrot,
    SeedCabbage,
};

struct ObjectInfo
{
    std::string modelPath;
    std::string texturePath;
};