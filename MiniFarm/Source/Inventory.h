#pragma once

enum class EItemID
{
    // Tools
    Hoe,
    WateringCan,
    Sickle,

    // Seeds
    SeedCarrot,
    SeedCabbage,

    // Crops
    Carrot,
    Cabbage
};

class Inventory
{
public:
    void AddItem(EItemID id, int count);
    bool UseItem(EItemID id);
private:
	std::unordered_map<EItemID, int> items;
};
