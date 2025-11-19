#pragma once
#include "GameObject.h"

enum class ECropID;
class Crop : public GameObject
{
private:
    ECropID m_id;
    int   m_level = 0;
    float m_time = 0.f;
    float m_water = 0.f;

public:
    Crop(ECropID id);

    void Update(int dt) override;
    void AddWater(float amount);
};