#pragma once
#include "InteractableObject.h"

class Shop : public InteractableObject
{
public:
	Shop(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale,
		const std::string& model, const std::string& texture)
		: InteractableObject(pos, rot, scale)
	{
		m_model = ModelCache::Get(model, texture);
	}
	virtual void Interact(Player* player) override
	{
	}
};

