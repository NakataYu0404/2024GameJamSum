#pragma once
#include "Player.h"
class Player1 :
    public Player
{
protected:
    virtual void CheckMoveDirection()override;
};

