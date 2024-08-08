#pragma once
#include "ActorBase.h"

class InputManager;

class Player :
    public ActorBase
{

public:

    static constexpr float MOVE_SPEED = 5.0f;

    static constexpr float GRAVITY = 9.81;

    static constexpr VECTOR MODEL_CORRECTION_POS = { 0.0f,100.0f,0.0f };

    enum class State {
        Move,
        KnockBack,
        Fall,
    };

    Player();
    Player(const VECTOR& initPos);
    ~Player();

   virtual void Init()override;
   virtual void Update()override;
   virtual void Draw()override;
   virtual void DebugDraw()final;

   virtual const VECTOR& GetMoveDir();
   virtual void SetMoveDir(const VECTOR& dir)final;

protected:

    InputManager& input_;

    State state_;

    bool isHitMove_;
    VECTOR moveDir_ = { 0.0f,0.0f,0.0f };
    float speed_ = 0.0f;
    float oldSpeed_ = 0.0f;

    // èâë¨ìx
    float movePow_ = 2.0f;
    // â¡ë¨ìx
    float moveAcc_ = 0.0f;

    virtual void CheckMoveDirection()final;
    virtual void ProcessMove()final;
    virtual void Move(const VECTOR& dir, float speed);
    float moveTotalTime_ = 0.0f;

    virtual void Gravity()final;
    float gravityTotalTime_ = 0.0f;

    // ìñÇΩÇËîªíË
    void CollisionStage();
};