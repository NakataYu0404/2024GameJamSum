#include <math.h>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/InputManager.h"
#include "../Object/Common/Transform.h"
#include "../Object/Common/CollisionManager.h"
#include "Camera.h"

Camera::Camera(void) : colMng_(CollisionManager::GetInstance())
{
	angles_ = VECTOR();
	cameraUp_ = VECTOR();
	mode_ = MODE::NONE;
	pos_ = AsoUtility::VECTOR_ZERO;
	targetPos_ = AsoUtility::VECTOR_ZERO;
	followTransform_ = nullptr;
}

Camera::~Camera(void)
{
}

void Camera::Init(void)
{
	ChangeMode(MODE::FIXED_POINT);
	midRayDestinationPos_ = AsoUtility::VECTOR_ZERO;
}

void Camera::Update(void)
{
}

void Camera::SetBeforeDraw(void)
{

	//	�N���b�v������ݒ肷��(SetDrawScreen�Ń��Z�b�g�����)
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
	
	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:
		SetBeforeDrawFixedPoint();
		break;
	case Camera::MODE::FOLLOW:
		SetBeforeDrawFollow();
		break;
	}

	//	�J�����̐ݒ�(�ʒu�ƒ����_�ɂ�鐧��)
	SetCameraPositionAndTargetAndUpVec(
		pos_, 
		targetPos_, 
		cameraUp_
	);

	midRayDestinationPos_ = VAdd(pos_, VScale(GetForward(), MIDPOS_STRETCH_POW));

	//	DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();

}

void Camera::Draw(void)
{
}

void Camera::SetFollow(const Transform* follow)
{
	followTransform_ = follow;
}

VECTOR Camera::GetMidRayDestantionPos(void)
{
	return midRayDestinationPos_;
}

VECTOR Camera::GetPos(void) const
{
	return pos_;
}

VECTOR Camera::GetAngles(void) const
{
	return angles_;
}

VECTOR Camera::GetTargetPos(void) const
{
	return targetPos_;
}

Quaternion Camera::GetQuaRot(void) const
{
	return rot_;
}

Quaternion Camera::GetQuaRotOutX(void) const
{
	return rotOutX_;
}

VECTOR Camera::GetForward(void) const
{
	return VNorm(VSub(targetPos_, pos_));
}

void Camera::ChangeMode(MODE mode)
{

	//	�J�����̏����ݒ�
	SetDefault();

	//	�J�������[�h�̕ύX
	mode_ = mode;

	//	�ύX���̏���������
	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:
		break;
	case Camera::MODE::FOLLOW:
		break;

	}

}

void Camera::SetDefault(void)
{

	//	�J�����̏����ݒ�
	pos_ = DEFAULT_CAMERA_POS;

	//	�����_
	targetPos_ = AsoUtility::VECTOR_ZERO;

	//	�J�����̏����
	cameraUp_ = AsoUtility::DIR_U;

	angles_.x = AsoUtility::Deg2RadF(30.0f);
	angles_.y = 0.0f;
	angles_.z = 0.0f;

	rot_ = Quaternion();

}

void Camera::SyncFollow(void)
{

	//	������̈ʒu
	VECTOR pos = followTransform_->pos;

	//	�d�͂̕�������ɏ]��
	//	���ʂ���ݒ肳�ꂽY�����A��]������
	rotOutX_ = Quaternion::AngleAxis(angles_.y, AsoUtility::AXIS_Y);

	//	���ʂ���ݒ肳�ꂽX�����A��]������
	rot_ = rotOutX_.Mult(Quaternion::AngleAxis(angles_.x, AsoUtility::AXIS_X));

	VECTOR localPos;

	//	�����_(�ʏ�d�͂ł����Ƃ����Y�l��Ǐ]�ΏۂƓ����ɂ���)
	localPos = rotOutX_.PosAxis(LOCAL_F2T_POS);
	targetPos_ = VAdd(pos, localPos);

	//	�J�����ʒu
	localPos = rot_.PosAxis(LOCAL_F2C_POS);

	VECTOR tmpPos = VAdd(pos, localPos);


	//	�J�����̏����
	cameraUp_ = AsoUtility::DIR_U;

}

void Camera::ProcessRot(void)
{
	auto& ins = InputManager::GetInstance();
	if (angles_.x <= LIMIT_X_UP_RAD)
	{
		if (ins.IsNew(KEY_INPUT_UP))
		{
			angles_.x += AsoUtility::Deg2RadF(CAMERA_ROT_SPEED);
		}
	}
	if (angles_.x >= LIMIT_X_DW_RAD)
	{
		if (ins.IsNew(KEY_INPUT_DOWN))
		{
			angles_.x -= AsoUtility::Deg2RadF(CAMERA_ROT_SPEED);
		}
	}

	if (ins.IsNew(KEY_INPUT_LEFT))
	{
		angles_.y -= AsoUtility::Deg2RadF(CAMERA_ROT_SPEED);
	}
	if (ins.IsNew(KEY_INPUT_RIGHT))
	{
		angles_.y += AsoUtility::Deg2RadF(CAMERA_ROT_SPEED);
	}

}


void Camera::SetBeforeDrawFixedPoint(void)
{
	//	�������Ȃ�
}

void Camera::SetBeforeDrawFollow(void)
{
	//	�J��������
	ProcessRot();

	//	�Ǐ]�ΏۂƂ̑��Έʒu�𓯊�
	SyncFollow();
}
