#pragma once
#include "Player.h"
class Player2 :
    public Player
{

    using Player::Player;

protected:
    virtual void CheckMoveDirection()override;
};

