#pragma once
#include "Player.h"
class Player1 :
    public Player
{
public:
    using Player::Player;

    //  �������牽���Ɍp������킯�ł��Ȃ������Ȃ̂ɁAvirtual���g���Ӗ��������܂���B
    virtual void InitModel()override;
protected:
    virtual const bool& IsInputMove()override;
    virtual void CheckMoveDirection()override;
};

