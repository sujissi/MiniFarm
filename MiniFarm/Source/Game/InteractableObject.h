#pragma once
#include "GameObject.h"
#include "IInteractable.h"

class InteractableObject : public GameObject, public IInteractable
{
public:
    InteractableObject(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
        :GameObject(pos, rot, scale)
    {
    }

    virtual bool IsInteractable() const override { return true; }
    virtual IInteractable* AsInteractable() override { return this; }
};
