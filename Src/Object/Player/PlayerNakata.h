#pragma once
#include <memory>
#include <vector>
#include "../ActorBase.h"

//	すでに先人がPlayerでGameSceneにクラスを作ったりしていたので、その遺物を利用するために名前をPlayerにした
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

	bool GetAlive(void);
private:

	//	回転完了までの時間
	static constexpr float TIME_ROT = 0.6f;

	void ProcessMove(void);
	void Move(void);

	void Accele(void);
	void Decelerate(void);

	void AddGravity(void);
	void Rotate(void);

	void SetGoalRotate(double rotRad);

	//	最終的な移動量
	VECTOR movePow_;

	//	追加の速度
	VECTOR AddSpeed_;

	//	
	float speed_;

	VECTOR moveDir_;

	int plNum_;

	VECTOR movedPos_;
	VECTOR gravHitPosUp_;
	VECTOR gravHitPosDown_;

	float gravityPow_;

	//	シングルトン参照
	CollisionManager& colMng_;

	bool isAlive_;

	std::vector<std::weak_ptr<Player>> players_;

	std::shared_ptr<Transform> charactorTran_;

	float rotRad_;

	int ForwardKey_;
	int BackKey_;
	int RightKey_;
	int LeftKey_;

	Quaternion goalQuaRot_;
	Quaternion playerRotY_;
	float stepRotTime_;
};

