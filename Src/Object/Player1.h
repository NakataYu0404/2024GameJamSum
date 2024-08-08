#pragma once
#include "Player.h"
class Player1 :
    public Player
{
public:
    using Player::Player;

    //  ここから何かに継承するわけでもなさそうなのに、virtualを使う意味を感じません。
    virtual void InitModel()override;
protected:
    virtual const bool& IsInputMove()override;
    virtual void CheckMoveDirection()override;
};

