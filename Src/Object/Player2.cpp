#include "Player2.h"
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"

void Player2::InitModel()
{
	transform_->modelId = MV1LoadModel("PlayerData/Model/X bot.mv1");
	transform_->quaRot = Quaternion();
	transform_->quaRotLocal = Quaternion::Euler({ 0.0f,AsoUtility::Deg2RadF(180.0f),0.0f });
}

const bool& Player2::IsInputMove()
{
	// ��(�p�b�h�Ή�)
	if (input_.IsNew(KEY_INPUT_UP)) return true;
	if (input_.IsNew(KEY_INPUT_LEFT)) return true;
	if (input_.IsNew(KEY_INPUT_DOWN)) return true;
	if (input_.IsNew(KEY_INPUT_RIGHT)) return true;
	return false;
}

void Player2::CheckMoveDirection()
{
	VECTOR oldMoveDir = moveDir_;

	if (input_.IsNew(KEY_INPUT_UP)) {
		moveDir_ = { 0.0f,0.0f,1.0f };
	}
	if (input_.IsNew(KEY_INPUT_LEFT)) {
		moveDir_ = { -1.0f,0.0f,0.0f };
	}
	if (input_.IsNew(KEY_INPUT_DOWN)) {
		moveDir_ = { 0.0f,0.0f,-1.0f };
	}
	if (input_.IsNew(KEY_INPUT_RIGHT)) {
		moveDir_ = { 1.0f,0.0f,0.0f };
	}

	// �ړ�������؂�ւ����Ƃ��Ɋp�x�̐��l�Ō����I
	if (IsInputMove()) {
		// �p�x���v�Z
		float angle = acosf(VDot(VNorm(oldMoveDir), VNorm(moveDir_)));
		float angleFactor = (1.0f - (angle / DX_PI));
		moveAcc_ *= angleFactor;
	}
}
