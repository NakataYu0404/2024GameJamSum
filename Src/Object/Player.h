#pragma once
#include "ActorBase.h"
#include <memory>

class InputManager;
class AnimationController;

using namespace std;

class Player :
    public ActorBase
{

public:

    static constexpr float MOVE_SPEED = 2.0f;

    static constexpr float MOVE_ACC_MAX = 1.0f;

    static constexpr float GRAVITY = 9.81;

    static constexpr float ROT_COM_SEC = 1.0f;

    static constexpr VECTOR MODEL_CORRECTION_POS = { 0.0f,100.0f,0.0f };

    // �m�b�N�o�b�N���؂�ւ��\
    static constexpr float CHANGEABLE_KNOCKBACK_POW = 0.35;

    // �m�b�N�o�b�N�̌����X�s�[�h
    static constexpr float KNOCKBACK_SPEED = 1.5;

    enum class State {
        Move,
        KnockBack,
        Fall,
        None,
    };

    enum class AnimType {
        Move,
        Landing
    };

    Player();
    Player(const VECTOR& initPos);
    ~Player();

   virtual void Init()override;
   virtual void InitModel() = 0;
   virtual void Update()override;
   virtual void Draw()override;
   virtual void DebugDraw()final;

   virtual const VECTOR& GetMoveDir();
   virtual const float GetMoveAcc();

   virtual void SetMoveDir(const VECTOR& dir)final;

   virtual void ProcessKnockBack(const VECTOR& dir, float pow);

protected:

    InputManager& input_;

    shared_ptr<AnimationController> anim_;

    Transform sphereModel_;

    State state_;

    // �A�b�v�f�[�g	// �A�b�v�f�[�g�Ǘ�
    using UpdateFunc_t = void (Player::*)();
    UpdateFunc_t updateFunc_ = &Player::UpdateMove;
    virtual void UpdateMove()final;
    virtual void UpdateKnockBack()final;
    virtual void UpdateFall()final;

    VECTOR moveDir_ = { 0.0f,0.0f,0.0f };
    float speed_ = 0.0f;
    float oldSpeed_ = 0.0f;

    // �����x
    float movePow_ = 2.0f;
    // �����x
    float moveAcc_ = 0.0f;

    // �L�[��������(�ړ����������肷��);
    virtual const bool& IsInputMove() = 0;
    virtual void CheckMoveDirection() = 0;

    // �ړ�
    virtual void ProcessMove()final;
    virtual void Move(const VECTOR& dir, float speed)final;
    float moveTotalTime_ = 0.0f;

    VECTOR velocity_ = {0.0f,0.0f,0.0f};

    // �m�b�N�o�b�N
    virtual void KnockBack();
    VECTOR knockBackDir_ = { 0.0f,0.0f,1.0f };
    float KnockBackPow_ = 1.1f;
    float knockBackTotalTime_ = 0.0f;
    float knockBackComTime_ = 0.0f;

    // ����
    virtual void Gravity()final;
    float gravityTotalTime_ = 0.0f;

    // �����蔻��
    virtual void CollisionStage()final;

    // ��]
    virtual void Rotation()final;
};