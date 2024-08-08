#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../../Utility/AsoUtility.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SceneManager.h"
#include "../Common/CollisionManager.h"
#include "../Common/EffectController.h"
#include "../Common/Sphere.h"
#include "PlayerNakata.h"

Player::Player(int plNum) : colMng_(CollisionManager::GetInstance())
{
	plNum_ = plNum;
}

Player::~Player()
{
}

void Player::Init(void)
{
	transform_ = std::make_shared<Transform>();
	SetParam();
}

void Player::Update(void)
{
	ProcessMove();
	Accele();
	Move();
	Decelerate();
	AddGravity();

	transform_->pos = movedPos_;

	transform_->Update();
}

void Player::Draw(void)
{
	MV1DrawModel(transform_->modelId);
	DrawSphere3D(sphere_->GetPos(), sphere_->GetRadius(),16, 0xffffff, 0xffffff, true);
}

void Player::SetParam(void)
{
	auto& resIns = resMng_.GetInstance();

	sphere_ = std::make_shared<Sphere>(transform_);

	switch (plNum_)
	{
	case 0:
		transform_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_PLAYER_BALL1));
		transform_->pos = { -100.0f,0.0f,100.0f };

		transform_->MakeCollider(Collider::Category::PLAYER1, Collider::TYPE::SPHERE);
		break;
	case 1:
		transform_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_PLAYER_BALL1));
		transform_->pos = { -100.0f,0.0f,-100.0f };

		transform_->MakeCollider(Collider::Category::PLAYER2, Collider::TYPE::SPHERE);
		break;
	case 2:
		transform_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_PLAYER_BALL1));
		transform_->pos = { 100.0f,0.0f,100.0f };

		transform_->MakeCollider(Collider::Category::PLAYER3, Collider::TYPE::SPHERE);
		break;
	case 3:
		transform_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_PLAYER_BALL1));
		transform_->pos = { 100.0f,0.0f,-100.0f };

		transform_->MakeCollider(Collider::Category::PLAYER4, Collider::TYPE::SPHERE);
		break;
	}

	transform_->quaRot = Quaternion();
	transform_->scl = { 0.5f,0.5f,0.5f };

	transform_->Update();

	sphere_->SetRadius(50.0f);
	sphere_->SetLocalPos({0.0f, 50.0f, 0.0f});

	movePow_ = { 0.0f,0.0f,0.0f };
	AddSpeed_ = { 0.0f,0.0f,0.0f };
	speed_ = 0.007f;
	moveDir_ = { 0.0f,0.0f,0.0f };

	movedPos_ = { 0.0f,0.0f,0.0f };
	gravHitPosUp_ = { 0.0f,0.0f,0.0f };
	gravHitPosDown_ = { 0.0f,0.0f,0.0f };

	isAlive_ = true;
}

void Player::OnCollision(std::weak_ptr<Collider> collider)
{
	int i = 0;
	switch (collider.lock()->category_)
	{
	case Collider::Category::PLAYER1:
		AddSpeed_ = AsoUtility::VDiv(VAdd(AddSpeed_, AsoUtility::VNormalize(AsoUtility::DistanceV(players_[0].lock()->GetTransform().lock()->pos, transform_->pos))), 5.0f);
		break;
	case Collider::Category::PLAYER2:
		AddSpeed_ = AsoUtility::VDiv(VAdd(AddSpeed_, AsoUtility::VNormalize(AsoUtility::DistanceV(players_[0].lock()->GetTransform().lock()->pos, transform_->pos))), 5.0f);
		break;
	case Collider::Category::PLAYER3:
		AddSpeed_ = AsoUtility::VDiv(VAdd(AddSpeed_, AsoUtility::VNormalize(AsoUtility::DistanceV(players_[0].lock()->GetTransform().lock()->pos, transform_->pos))), 5.0f);
		break;
	case Collider::Category::PLAYER4:
		AddSpeed_ = AsoUtility::VDiv(VAdd(AddSpeed_, AsoUtility::VNormalize(AsoUtility::DistanceV(players_[0].lock()->GetTransform().lock()->pos, transform_->pos))), 5.0f);
		break;
	case Collider::Category::STAGE:
		transform_->pos = collider.lock()->hitInfo_.movedPos;
		transform_->Update();
		break;
	}
}

void Player::SetPlayers(std::weak_ptr<Player> player)
{
	players_.push_back(player);
}

VECTOR Player::GetSpeedVec(void)
{
	return AddSpeed_;
}

bool Player::GetAlive(void)
{
	return isAlive_;
}

void Player::ProcessMove(void)
{
	auto& input = InputManager::GetInstance();

	// プレイヤーの入力を検知する
	auto playerCtl = input.GetJPadInputState(static_cast<InputManager::JOYPAD_NO>(plNum_ + 1));

	VECTOR dir = AsoUtility::VECTOR_ZERO;

	dir.x = playerCtl.AKeyLX;
	dir.z = playerCtl.AKeyLY * -1;


	// dirは方向ベクトルのことだが、コントローラーの入力を10段階(N状態を除く)にしたので0～10になっている。最大値は1.0fの方が仕様上良いので除算する。
	dir.x /= 10.0f;
	dir.z /= 10.0f;

	if (dir.x > 0.1f || input.IsNew(KEY_INPUT_D))
	{
		dir.x = 1.0f;
	}
	if (dir.z > 0.1f || input.IsNew(KEY_INPUT_W))
	{
		dir.z = 1.0f;
	}

	if (dir.x < -0.1f || input.IsNew(KEY_INPUT_A))
	{
		dir.x = -1.0f;
	}
	if (dir.z < -0.1f || input.IsNew(KEY_INPUT_S))
	{
		dir.z = -1.0f;
	}

	float stickAngle = atan2f(dir.x, dir.z);

	if (!AsoUtility::EqualsVZero(dir)) {
		dir = AsoUtility::VNormalize(dir);
	}

	//	プレイヤーが向きたい角度
	//rotRad_ = stickAngle;

	if (!AsoUtility::EqualsVZero(dir)) {

		moveDir_ = dir;

		//	回転処理
		//SetGoalRotate(rotRad_);

	}
	else
	{
		moveDir_ = dir;
	}

}


void Player::Move(void)
{
	movedPos_ = VAdd(transform_->pos, movePow_);
}

void Player::Accele(void)
{
	AddSpeed_ = VAdd(AddSpeed_, VScale(moveDir_,speed_));

	if (AddSpeed_.x > MAX_SPEED)
	{
		AddSpeed_.x = MAX_SPEED;
	}
	if (AddSpeed_.z > MAX_SPEED)
	{
		AddSpeed_.z = MAX_SPEED;
	}
	if (AddSpeed_.x < MIN_SPEED)
	{
		AddSpeed_.x = MIN_SPEED;
	}
	if (AddSpeed_.z < MIN_SPEED)
	{
		AddSpeed_.z = MIN_SPEED;
	}


	movePow_ = VAdd(movePow_, AddSpeed_);
}

void Player::Decelerate(void)
{
	movePow_ = VScale(movePow_, 0.9f);
	if (movePow_.x < 0.0001f && movePow_.x > -0.0001f)
	{
		movePow_.x = 0.0f;
	}
	if (movePow_.z < 0.0001f && movePow_.z > -0.0001f)
	{
		movePow_.z = 0.0f;
	}

	AddSpeed_ = VScale(AddSpeed_, 0.98f);
	if (AddSpeed_.x < 0.0001f && AddSpeed_.x > -0.0001f)
	{
		AddSpeed_.x = 0.0f;
	}
	if (AddSpeed_.z < 0.0001f && AddSpeed_.z > -0.0001f)
	{
		AddSpeed_.z = 0.0f;
	}
}

void Player::AddGravity(void)
{
	//	重力の強さ
	float gravityPow = 10.0f;

	//	ジャンプ量を加算
	movedPos_.y -= gravityPow;

	//	重力方向
	VECTOR dirGravity = AsoUtility::DIR_D;

	//	重力方向の反対
	VECTOR dirUpGravity = AsoUtility::DIR_U;


	float checkPow = 20.0f;
	gravHitPosUp_ = VAdd(movedPos_, VScale(dirUpGravity, gravityPow));
	gravHitPosUp_ = VAdd(gravHitPosUp_, VScale(dirUpGravity, checkPow * 2.0f));
	gravHitPosDown_ = VAdd(movedPos_, VScale(dirGravity, checkPow));

	auto hit = colMng_.GetInstance().Line_IsCollision_Stage(gravHitPosUp_, gravHitPosDown_);

	if (hit.HitFlag > 0)
	{
		//	衝突地点から、少し上に移動
		movedPos_ = VAdd(hit.HitPosition, VScale(dirUpGravity, gravityPow));

		gravityPow_ = DEFAULT_GRAVITY_POW;

	}

}
