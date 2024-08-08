#include "Player1.h"
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"

void Player1::InitModel()
{
    //  Player�ł��L�q����Ă��܂���ł������H
    //  ���ƁAData�t�H���_������̂ɓ����K�w�ɏ����PlayerData�Ƃ������킯�킩���t�H���_�����Ȃ��ŉ������B�ז��ł��BData/Model/Player�Ɉړ������܂����B
    //  ���ƁAResourceManager���g���ĉ������B
    //  ���ƁA�t�@�C�����ɃX�y�[�X��p���Ȃ��ł��������B
	transform_->modelId = MV1LoadModel("PlayerData/Model/X bot.mv1");
	transform_->quaRot = Quaternion();
	transform_->quaRotLocal = Quaternion::Euler({ 0.0f,AsoUtility::Deg2RadF(180.0f),0.0f });
}

const bool& Player1::IsInputMove()
{
	// ��(�p�b�h�Ή�)
	if (input_.IsNew(KEY_INPUT_W)) return true;
	if (input_.IsNew(KEY_INPUT_A)) return true;
	if (input_.IsNew(KEY_INPUT_S)) return true;
	if (input_.IsNew(KEY_INPUT_D)) return true;
	return false;
}

void Player1::CheckMoveDirection()
{
    VECTOR oldMoveDir = moveDir_;

    if (input_.IsNew(KEY_INPUT_W)) {
        moveDir_ = { 0.0f,0.0f,1.0f };
    }
    if (input_.IsNew(KEY_INPUT_A)) {
        moveDir_ = { -1.0f,0.0f,0.0f };
    }
    if (input_.IsNew(KEY_INPUT_S)) {
        moveDir_ = { 0.0f,0.0f,-1.0f };
    }
    if (input_.IsNew(KEY_INPUT_D)) {
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
