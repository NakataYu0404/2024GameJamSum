#include "Player1.h"
#include "../Manager/InputManager.h"

void Player1::CheckMoveDirection()
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
