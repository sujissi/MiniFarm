#pragma once
#include "GameObject.h"
#include "IInteractable.h"

class InteractableObject : public GameObject, public IInteractable
{
public:
    virtual bool IsInteractable() const override { return true; }
    virtual IInteractable* AsInteractable() override { return this; }
};
