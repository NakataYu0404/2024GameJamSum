#pragma once
#include "ActorBase.h"

class InputManager;

class Player :
    public ActorBase
{

public:

    static constexpr float MOVE_SPEED = 5.0f;

    static constexpr float GRAVITY = 9.81;

    static constexpr float ROT_COM_SEC = 1.0f;

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
   virtual const float GetMoveAcc();

   virtual void SetMoveDir(const VECTOR& dir)final;

   virtual void SwitchMoveDir();

   virtual void ProcessKnockBack(const VECTOR& dir, float pow);

protected:

    // �A�b�v�f�[�g	// �A�b�v�f�[�g�Ǘ�
    using UpdateFunc_t = void (Player::*)();
    UpdateFunc_t updateFunc_ = &Player::UpdateMove;
    virtual void UpdateMove()final;
    virtual void UpdateKnockBack()final;
    virtual void UpdateFall()final;

    InputManager& input_;

    State state_;

    bool isHitMove_;
    VECTOR moveDir_ = { 0.0f,0.0f,0.0f };
    float speed_ = 0.0f;
    float oldSpeed_ = 0.0f;

    // �����x
    float movePow_ = 2.0f;
    // �����x
    float moveAcc_ = 0.0f;

    // �m�b�N�o�b�N
    virtual void KnockBack();
    VECTOR knockBackDir_ = { 0.0f,0.0f,1.0f };
    float KnockBackPow_ = 1.1f;
    float knockBackTotalTime_ ;

    // �ړ�
    virtual void CheckMoveDirection() = 0;
    virtual void ProcessMove()final;
    virtual void Move(const VECTOR& dir, float speed)final;
    float moveTotalTime_ = 0.0f;

    // ����
    virtual void Gravity()final;
    float gravityTotalTime_ = 0.0f;

    // �����蔻��
    virtual void CollisionStage()final;

    // ��]
    virtual void Rotation()final;
};