#include "Player.h"
#include "../Manager/InputManager.h"
#include "Common/Sphere.h"
#include "../Manager/SceneManager.h"
#include "../Utility/AsoUtility.h"
#include "Common/CollisionManager.h"

VECTOR VECTOR_ZERO = { 0.0f,0.0f,0.0f };

Player::Player() : input_(InputManager::GetInstance())
{
	transform_ = make_shared<Transform>();
	transform_->pos = { 0.0f,0.0f,0.0f };

	sphere_ = make_shared<Sphere>(transform_);
	sphere_->SetRadius(100.0f);

	state_ = State::Move;

	transform_->modelId = MV1LoadModel("PlayerData/Model/X bot.mv1");
	transform_->quaRot = Quaternion();
	transform_->quaRotLocal = Quaternion::Euler({ 0.0f,AsoUtility::Deg2RadF(180.0f),0.0f });
}

Player::Player(const VECTOR& initPos) : input_(InputManager::GetInstance())
{
	transform_ = make_shared<Transform>();
	transform_->pos = initPos;

	sphere_ = make_shared<Sphere>(transform_);
	sphere_->SetRadius(100.0f);

	state_ = State::Move;

	transform_->modelId = MV1LoadModel("PlayerData/Model/X bot.mv1");
	transform_->quaRot = Quaternion();
	transform_->quaRotLocal = Quaternion::Euler({ 0.0f,AsoUtility::Deg2RadF(180.0f),0.0f });
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	CheckMoveDirection();

	if (input_.IsNew(KEY_INPUT_1)) {
		moveDir_ = VScale(moveDir_, -1);
	}

	ProcessMove();


	CollisionStage();
	Gravity();
	transform_->Update();
}

void Player::Draw()
{

	MV1DrawModel(transform_->modelId);
	DebugDraw();
}

void Player::DebugDraw()
{
	DrawSphere3D(transform_->pos, sphere_->GetRadius(), 10, 0xffffff, 0xffffff, false);
	VECTOR StageCenterPos = { 0.0f,0.0f,0.0f };
	float StageRadius = 700.0f;
	DrawSphere3D(StageCenterPos, StageRadius, 10, 0xffffff, 0xffffff, false);
	DrawFormatString(0, 32, 0xffffff, "%f", speed_);
}

const VECTOR& Player::GetMoveDir()
{
	return moveDir_;
}

void Player::SetMoveDir(const VECTOR& dir)
{
	moveDir_ = dir;
}

void Player::CheckMoveDirection()
{

	isHitMove_ = false;
	if (input_.IsNew(KEY_INPUT_W)) {
		moveDir_ = { 0.0f,0.0f,1.0f };
		isHitMove_ = true;
	}
	if (input_.IsNew(KEY_INPUT_A)) {
		moveDir_ = { -1.0f,0.0f,0.0f };
		isHitMove_ = true;
	}
	if (input_.IsNew(KEY_INPUT_S)) {
		moveDir_ = { 0.0f,0.0f,-1.0f };
		isHitMove_ = true;
	}
	if (input_.IsNew(KEY_INPUT_D)) {
		moveDir_ = { 1.0f,0.0f,0.0f };
		isHitMove_ = true;
	}
}

void Player::ProcessMove()
{
	Move(moveDir_, MOVE_SPEED);
}

void Player::Move(const VECTOR& dir, float speed)
{
	// â¡ë¨èàóù
	float deltaTime = SceneManager::GetInstance().GetDeltaTime();
	if (isHitMove_){
		moveAcc_ += speed * deltaTime;
		if (moveAcc_ > 1) {
			moveAcc_ = 1;
		}
	}
	transform_->pos = VAdd(transform_->pos, VScale(moveDir_, moveAcc_));

	// å∏ë¨èàóù
	moveAcc_ -= speed * 0.15f * deltaTime;
	if (moveAcc_ < 0.0f) {
		moveAcc_ = 0.0f;
		moveDir_ = { 0.0f,0.0f,0.0f };
	}
}

void Player::Gravity()
{
	if (state_ != State::Fall) return;

	gravityTotalTime_ += SceneManager::GetInstance().GetDeltaTime();
	transform_->pos.y += -0.5 * GRAVITY * gravityTotalTime_ * gravityTotalTime_;
}

void Player::CollisionStage()
{
	VECTOR StageCenterPos = { 0.0f,0.0f,0.0f };
	float StageRadius = 700.0f;

	float Distance = sqrtf(pow((StageCenterPos.x - transform_->pos.x), 2) + pow((StageCenterPos.z - transform_->pos.z), 2));

	if (StageRadius < Distance) {
		state_ = State::Fall;
	}
}
