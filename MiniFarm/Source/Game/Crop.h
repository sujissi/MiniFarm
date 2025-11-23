#pragma once
#include "InteractableObject.h"

enum class ECropID;
class Crop : public InteractableObject
{
private:
    ECropID m_id;
    int   m_level = 0;
    float m_time = 0.f;
    float m_water = 0.f;

public:
    Crop(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale,
        const std::string& model, const std::string& texture);

	void SetCropID(ECropID id) { m_id = id; }
    void Update(int dt) override;
    void AddWater(float amount);

    virtual void Interact(Player* player) override;
};