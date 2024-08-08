#include "Player2.h"
#include "../Manager/InputManager.h"

void Player2::CheckMoveDirection()
{
	isHitMove_ = false;
	if (input_.IsNew(KEY_INPUT_UP)) {
		moveDir_ = { 0.0f,0.0f,1.0f };
		isHitMove_ = true;
	}
	if (input_.IsNew(KEY_INPUT_LEFT)) {
		moveDir_ = { -1.0f,0.0f,0.0f };
		isHitMove_ = true;
	}
	if (input_.IsNew(KEY_INPUT_DOWN)) {
		moveDir_ = { 0.0f,0.0f,-1.0f };
		isHitMove_ = true;
	}
	if (input_.IsNew(KEY_INPUT_RIGHT)) {
		moveDir_ = { 1.0f,0.0f,0.0f };
		isHitMove_ = true;
	}
}
