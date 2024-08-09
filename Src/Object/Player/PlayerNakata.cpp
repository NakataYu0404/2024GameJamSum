#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../../Utility/AsoUtility.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/Camera.h"
#include "../Common/AnimationController.h"
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
	charactorTran_ = std::make_shared<Transform>();

	SetParam();

	// ���ǉ����܂�
	sndRoll_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::SND_ROLL_1).handleId_;
	sndHit_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::SND_HIT).handleId_;
}

void Player::Update(void)
{
	ProcessMove();
	Accele();
	Move();
	Decelerate();
	AddGravity();

	Rotate();

	transform_->pos = movedPos_;

	transform_->Update();
	charactorTran_->pos = { transform_->pos.x,transform_->pos.y + 100.0f,transform_->pos.z };
	charactorTran_->quaRot = playerRotY_;
	charactorTran_->Update();

	if (transform_->pos.y <= -1000.0f)
	{
		isAlive_ = false;
	}
}

void Player::Draw(void)
{
	MV1DrawModel(transform_->modelId);
	MV1DrawModel(charactorTran_->modelId);
	//DrawSphere3D(sphere_->GetPos(), sphere_->GetRadius(),16, 0xffffff, 0xffffff, true);
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

		charactorTran_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_PLAYER_RED));
		charactorTran_->pos = { transform_->pos.x,transform_->pos.y + 100.0f,transform_->pos.z };

		transform_->MakeCollider(Collider::Category::PLAYER1, Collider::TYPE::SPHERE);
		
		break;
	case 1:
		transform_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_PLAYER_BALL2));
		transform_->pos = { -100.0f,0.0f,-100.0f };

		charactorTran_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_PLAYER_GREEN));
		charactorTran_->pos = { transform_->pos.x,transform_->pos.y + 100.0f,transform_->pos.z };

		transform_->MakeCollider(Collider::Category::PLAYER2, Collider::TYPE::SPHERE);
		break;
	case 2:
		transform_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_PLAYER_BALL3));
		transform_->pos = { 100.0f,0.0f,100.0f };

		charactorTran_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_PLAYER_BLUE));
		charactorTran_->pos = { transform_->pos.x,transform_->pos.y + 100.0f,transform_->pos.z };

		transform_->MakeCollider(Collider::Category::PLAYER3, Collider::TYPE::SPHERE);
		break;
	case 3:
		transform_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_PLAYER_BALL4));
		transform_->pos = { 100.0f,0.0f,-100.0f };

		charactorTran_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_PLAYER_YELLOW));
		charactorTran_->pos = { transform_->pos.x,transform_->pos.y + 100.0f,transform_->pos.z };

		transform_->MakeCollider(Collider::Category::PLAYER4, Collider::TYPE::SPHERE);
		break;
	}

	transform_->quaRot = Quaternion();
	charactorTran_->quaRot = Quaternion();
	charactorTran_->quaRotLocal =
		Quaternion::Euler({ 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f });

	transform_->scl = { 0.5f,0.5f,0.5f };
	charactorTran_->scl = { 0.5f,0.5f,0.5f };

	transform_->Update();
	charactorTran_->Update();

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
	rotRad_ = 0.0f;
	playerRotY_ = Quaternion();
	goalQuaRot_ = Quaternion();
	stepRotTime_ = 0.0f;

}

void Player::OnCollision(std::weak_ptr<Collider> collider)
{
	int i = 0;

	// ���ǉ����܂�
	PlaySoundMem(sndHit_, DX_PLAYTYPE_BACK);

	switch (collider.lock()->category_)
	{
	case Collider::Category::PLAYER1:
		AddSpeed_ = AsoUtility::VDiv(VAdd(AddSpeed_, AsoUtility::VNormalize(AsoUtility::DistanceV(players_[0].lock()->GetTransform().lock()->pos, transform_->pos))), 3.0f);
		break;
	case Collider::Category::PLAYER2:
		AddSpeed_ = AsoUtility::VDiv(VAdd(AddSpeed_, AsoUtility::VNormalize(AsoUtility::DistanceV(players_[1].lock()->GetTransform().lock()->pos, transform_->pos))), 3.0f);
		break;
	case Collider::Category::PLAYER3:
		AddSpeed_ = AsoUtility::VDiv(VAdd(AddSpeed_, AsoUtility::VNormalize(AsoUtility::DistanceV(players_[2].lock()->GetTransform().lock()->pos, transform_->pos))), 3.0f);
		break;
	case Collider::Category::PLAYER4:
		AddSpeed_ = AsoUtility::VDiv(VAdd(AddSpeed_, AsoUtility::VNormalize(AsoUtility::DistanceV(players_[3].lock()->GetTransform().lock()->pos, transform_->pos))), 3.0f);
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

	// �v���C���[�̓��͂����m����
	auto playerCtl = input.GetJPadInputState(static_cast<InputManager::JOYPAD_NO>(plNum_ + 1));

	VECTOR dir = AsoUtility::VECTOR_ZERO;

	dir.x = playerCtl.AKeyLX;
	dir.z = playerCtl.AKeyLY * -1;


	// dir�͕����x�N�g���̂��Ƃ����A�R���g���[���[�̓��͂�10�i�K(N��Ԃ�����)�ɂ����̂�0�`10�ɂȂ��Ă���B�ő�l��1.0f�̕����d�l��ǂ��̂ŏ��Z����B
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

	//	�v���C���[�����������p�x
	rotRad_ = stickAngle;

	if (!AsoUtility::EqualsVZero(dir)) {

		moveDir_ = dir;

		//	��]����
		SetGoalRotate(rotRad_);

	}
	else
	{
		moveDir_ = dir;
	}

}

void Player::SetGoalRotate(double rotRad)
{
	VECTOR cameraRot;
	Quaternion axis;
	Quaternion axis2;

	cameraRot = SceneManager::GetInstance().GetCamera()->GetAngles();
	axis = Quaternion::AngleAxis(AsoUtility::RadIn2PI((double)cameraRot.y + rotRad), AsoUtility::AXIS_Y);

	//	���ݐݒ肳��Ă����]�Ƃ̊p�x�������
	double angleDiff = Quaternion::Angle(axis, goalQuaRot_);

	//	�������l
	if (angleDiff > 0.01)
	{
		stepRotTime_ = TIME_ROT;
	}

	goalQuaRot_ = axis;

}

void Player::Rotate(void)
{

	stepRotTime_ -= scnMng_.GetDeltaTime();

	//	��]�̋��ʕ��
	playerRotY_ = Quaternion::Slerp(
		playerRotY_, goalQuaRot_, (TIME_ROT - stepRotTime_) / TIME_ROT);
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
	//	�d�͂̋���
	float gravityPow = 10.0f;

	//	�W�����v�ʂ����Z
	movedPos_.y -= gravityPow;

	//	�d�͕���
	VECTOR dirGravity = AsoUtility::DIR_D;

	//	�d�͕����̔���
	VECTOR dirUpGravity = AsoUtility::DIR_U;


	float checkPow = 20.0f;
	gravHitPosUp_ = VAdd(movedPos_, VScale(dirUpGravity, gravityPow));
	gravHitPosUp_ = VAdd(gravHitPosUp_, VScale(dirUpGravity, checkPow * 2.0f));
	gravHitPosDown_ = VAdd(movedPos_, VScale(dirGravity, checkPow));

	auto hit = colMng_.GetInstance().Line_IsCollision_Stage(gravHitPosUp_, gravHitPosDown_);

	if (hit.HitFlag > 0)
	{
		//	�Փ˒n�_����A������Ɉړ�
		movedPos_ = VAdd(hit.HitPosition, VScale(dirUpGravity, gravityPow));

		gravityPow_ = DEFAULT_GRAVITY_POW;

	}

}
