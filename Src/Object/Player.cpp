#include "Player.h"
#include "../Manager/InputManager.h"
#include "Common/Sphere.h"
#include "../Manager/SceneManager.h"
#include "../Utility/AsoUtility.h"
#include "Common/CollisionManager.h"
#include "../Manager/Camera.h"

VECTOR VECTOR_ZERO = { 0.0f,0.0f,0.0f };

Player::Player() : input_(InputManager::GetInstance())
{
	transform_ = make_shared<Transform>();
	transform_->pos = { 0.0f,0.0f,0.0f };
	Init();
	InitModel();
}

Player::Player(const VECTOR& initPos) : input_(InputManager::GetInstance())
{
	transform_ = make_shared<Transform>();
	transform_->pos = initPos;
	Init();
	InitModel();
}

Player::~Player()
{
}

void Player::Init()
{
	sphere_ = make_shared<Sphere>(transform_);
	sphere_->SetRadius(100.0f);
	state_ = State::Move;
}

void Player::InitModel()
{
	transform_->modelId = MV1LoadModel("PlayerData/Model/X bot.mv1");
	transform_->quaRot = Quaternion();
	transform_->quaRotLocal = Quaternion::Euler({ 0.0f,AsoUtility::Deg2RadF(180.0f),0.0f });
}

void Player::Update()
{
	(this->*updateFunc_)();

	CollisionStage();
	transform_->Update();
}

void Player::Draw()
{
	// ���f�����W�␳
	MV1SetPosition(transform_->modelId, VAdd(transform_->pos, MODEL_CORRECTION_POS));

	// ���f���\��
	MV1DrawModel(transform_->modelId);

	DebugDraw();
}

void Player::DebugDraw()
{
	DrawSphere3D(transform_->pos, sphere_->GetRadius(), 10, 0xffffff, 0xffffff, false);
	VECTOR StageCenterPos = { 0.0f,0.0f,100.0f };
	float StageRadius = 700.0f;
	DrawSphere3D(StageCenterPos, StageRadius, 10, 0xffffff, 0xffffff, false);
	DrawFormatString(0, 32, 0xffffff, "%f", speed_);
}

const VECTOR& Player::GetMoveDir()
{
	return moveDir_;
}

const float Player::GetMoveAcc()
{
	return moveAcc_;
}

void Player::SetMoveDir(const VECTOR& dir)
{
	moveDir_ = dir;
}

void Player::UpdateMove()
{
	// �ړ�
	CheckMoveDirection();
	ProcessMove();

	// ��]
	Rotation();
}

void Player::UpdateKnockBack()
{
	// �m�b�N�o�b�N
	KnockBack();
}

void Player::UpdateFall()
{
	// ����
	Gravity();
}

const bool& Player::IsInputMove()
{
	// ��(�p�b�h�Ή�)
	if (input_.IsNew(KEY_INPUT_W)) return true;
	if (input_.IsNew(KEY_INPUT_A)) return true;
	if (input_.IsNew(KEY_INPUT_S)) return true;
	if (input_.IsNew(KEY_INPUT_D)) return true;
	return false;
}

void Player::CheckMoveDirection()
{
	if (input_.IsNew(KEY_INPUT_W)) {
		moveDir_ = { 0.0f,0.0f,1.0f };
	}
	if (input_.IsNew(KEY_INPUT_A)) {
		moveDir_ = { -1.0f,0.0f,0.0f };
		moveAcc_ = 0.0f;
	}
	if (input_.IsNew(KEY_INPUT_S)) {
		moveDir_ = { 0.0f,0.0f,-1.0f };
	}
	if (input_.IsNew(KEY_INPUT_D)) {
		moveDir_ = { 1.0f,0.0f,0.0f };
	}
}

void Player::ProcessMove()
{
	Move(moveDir_, MOVE_SPEED);
}

void Player::Move(const VECTOR& dir, float speed)
{
	// ��������
	float deltaTime = SceneManager::GetInstance().GetDeltaTime();
	if (IsInputMove()){
		moveAcc_ += speed * deltaTime;
		if (moveAcc_ > MOVE_ACC_MAX) {
			moveAcc_ = MOVE_ACC_MAX;
		}
	}
	transform_->pos = VAdd(transform_->pos, VScale(moveDir_, moveAcc_));

	// ��������
	moveAcc_ -= speed * 0.05f * deltaTime;
	if (moveAcc_ < 0.0f) {
		moveAcc_ = 0.0f;
		moveDir_ = { 0.0f,0.0f,0.0f };
	}
}

void Player::ProcessKnockBack(const VECTOR& dir, float pow)
{
	knockBackDir_ = dir;
	KnockBackPow_ = pow;
	updateFunc_ = &Player::UpdateKnockBack;
	state_ = State::KnockBack;
	moveAcc_ = 0.0f;

	// �m�b�N�o�b�N��������
	knockBackComTime_ = KnockBackPow_ / (KNOCKBACK_SPEED * 0.15);
	knockBackTotalTime_ = 0.0f;
}

void Player::KnockBack()
{
	float deltaTime = SceneManager::GetInstance().GetDeltaTime();
	knockBackTotalTime_ += deltaTime;

	// �ړ�
	transform_->pos = VAdd(transform_->pos, VScale(knockBackDir_, KnockBackPow_));

	// ����
	KnockBackPow_ -= KNOCKBACK_SPEED * 0.15f * deltaTime;

	// �ړ��؂�ւ��\����
	// �o�ߎ��ԂőJ�ډ\�����߂�(55�p�[)
	if (knockBackTotalTime_ >= knockBackComTime_ * 0.55) {
		CheckMoveDirection();
		if (IsInputMove()) {
			updateFunc_ = &Player::UpdateMove;
			state_ = State::Move;
		}
	}

	// �����I��
	if (KnockBackPow_ < 0.0f) {
		KnockBackPow_ = 0.0f;
		updateFunc_ = &Player::UpdateMove;
		state_ = State::Move;
	}
}

void Player::Gravity()
{
	// if (state_ != State::Fall) return;

	gravityTotalTime_ += SceneManager::GetInstance().GetDeltaTime();
	transform_->pos.y += -0.5 * GRAVITY * gravityTotalTime_ * gravityTotalTime_;
}

void Player::CollisionStage()
{
	// �X�e�[�W���
	VECTOR StageCenterPos = { 0.0f,0.0f,100.0f };
	float StageRadius = 2000.0f;

	// ����
	float Distance = sqrtf(pow((StageCenterPos.x - transform_->pos.x), 2) + pow((StageCenterPos.z - transform_->pos.z), 2));
	if (StageRadius < Distance) {
		updateFunc_ = &Player::UpdateFall;
		state_ = State::Fall;
	}
}

void Player::Rotation()
{
	if (!IsInputMove()) return;

	Quaternion cameraRot = SceneManager::GetInstance().GetCamera()->GetQuaRotOutX();
	VECTOR cRot = cameraRot.PosAxis(moveDir_);

	float deltaTime = SceneManager::GetInstance().GetDeltaTime();
	float comSec = ROT_COM_SEC / deltaTime;

	Quaternion goalQuaRot = Quaternion::LookRotation(cRot);
	transform_->quaRot = Quaternion::Slerp(transform_->quaRot, goalQuaRot, comSec);
}