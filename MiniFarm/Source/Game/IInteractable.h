#pragma once

class Player;

class IInteractable
{
public:
    virtual void Interact(Player* player) = 0;
};
