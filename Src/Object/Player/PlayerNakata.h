#pragma once
#include <memory>
#include <vector>
#include "../ActorBase.h"

//	���łɐ�l��Player��GameScene�ɃN���X��������肵�Ă����̂ŁA���̈╨�𗘗p���邽�߂ɖ��O��Player�ɂ���
class Player : public ActorBase
{
public:

	static constexpr float MAX_SPEED = 1.0f;
	static constexpr float MIN_SPEED = -1.0f;
	static constexpr float DEFAULT_GRAVITY_POW = -9.8f;

	Player(int plNum);
	~Player();

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetParam(void) override;

	void OnCollision(std::weak_ptr<Collider> collider) override;

	void SetPlayers(std::weak_ptr<Player> player);

	VECTOR GetSpeedVec(void);
private:

	void ProcessMove(void);
	void Move(void);

	void Accele(void);
	void Decelerate(void);

	void AddGravity(void);

	//	�ŏI�I�Ȉړ���
	VECTOR movePow_;

	//	�ǉ��̑��x
	VECTOR AddSpeed_;

	//	
	float speed_;

	VECTOR moveDir_;

	int plNum_;

	VECTOR movedPos_;
	VECTOR gravHitPosUp_;
	VECTOR gravHitPosDown_;

	float gravityPow_;

	//	�V���O���g���Q��
	CollisionManager& colMng_;

	bool isAlive_;

	std::vector<std::weak_ptr<Player>> players_;

	int ForwardKey_;
	int BackKey_;
	int RightKey_;
	int LeftKey_;

};

