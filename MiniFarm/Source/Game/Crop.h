#pragma once
#include "InteractableObject.h"

enum class EItemID;
class Crop : public InteractableObject
{
private:
    EItemID m_id;
    int   m_level = 0;
    float m_time = 0.f;
    float m_water = 0.f;

public:
    Crop(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale,
        const std::string& model, const std::string& texture);

	void SetCropID(EItemID id) { m_id = id; }
    void SetCropState(EItemID newID, int newLevel);
    void Update(int dt) override;
    void AddWater(float amount);
    virtual void OnInteract(Player* player) override;
};