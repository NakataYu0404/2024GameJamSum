#include <memory>
#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include "../Object/Common/AnimationController.h"

#include "../Object/Stage/Magma.h"
#include "GameScene.h"

#include "../Object/Player.h"
#include "../Object/Player1.h"
#include "../Object/Player2.h"
#include "../Object/Common/CollisionManager.h"
#include "../Object/Common/Sphere.h"

GameScene::GameScene(void)
{

	players_.push_back(make_shared<Player1>());
	VECTOR initPos = { 300.0f,0.0f,0.0f };
	players_.push_back(make_shared<Player2>(initPos));
	initPos = { 0.0f,0.0f,400.0f };
	players_.push_back(make_shared<Player2>(initPos));
	initPos = { 0.0f,0.0f,800.0f };
	players_.push_back(make_shared<Player2>(initPos));
	// players_.push_back(make_shared<Player2>());
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	inTypeGame_ = InSceneType::READY;

	magma_ = std::make_shared<Magma>();
	magma_->Init();
}

void GameScene::Update(void)
{
	switch (inTypeGame_)
	{
	case GameScene::InSceneType::READY:
		UpdateReady();
		break;
	case GameScene::InSceneType::INGAME:
		UpdateInGame();
		break;
	case GameScene::InSceneType::GAMEOVER:
		UpdateOver();
		break;
	default:
		break;
	}

	for (auto& p : players_) {
		p->Update();
	}
}

void GameScene::Draw(void)
{
	DrawFormatString(0, 0, 0xffffff, "Game");

	magma_->Draw();

	for (auto& p : players_) {
		p->Draw();
	}
	Collision();
}

void GameScene::UpdateReady(void)
{
	//	if(準備完了)
	//	{
	//		inTypeGame_ = InSceneType::INGAME;
	//	}
}

void GameScene::UpdateInGame(void)
{
	//	if(決着)
	//	{
	//		inTypeGame_ = InSceneType::GAMEOVER;
	//	}
}

void GameScene::UpdateOver(void)
{
}

void GameScene::Collision()
{
	for (auto& p1 : players_) {
		for (auto& p2 : players_) {
			if (p1 == p2) continue;
			float distance = VSize(VSub(p1->GetTransform().lock()->pos, p2->GetTransform().lock()->pos));
			float CollDistance = p1->GetSphere().lock()->GetRadius() + p2->GetSphere().lock()->GetRadius();

			// 衝突判定
			if (distance >= CollDistance) continue;

			// 速度比較
			float p1Acc = p1->GetMoveAcc();
			float p2Acc = p2->GetMoveAcc();

			// ノックバック方向計算
			VECTOR p1KnockBackDir = VNorm(VSub(p1->GetTransform().lock()->pos, p2->GetTransform().lock()->pos));
			VECTOR p2KnockBackDir = VScale(p1KnockBackDir, -1.0f);

			if (p1Acc == p2Acc) {
				// 両方にノックバック
				p1->ProcessKnockBack(p1KnockBackDir, 0.5f);
				p2->ProcessKnockBack(p2KnockBackDir, 0.5f);
			} 
			else {
				// 比率でノックバックをさせる
				float totalAcc = p1Acc + p2Acc;
				p1->ProcessKnockBack(p1KnockBackDir, p2Acc / totalAcc);
				p2->ProcessKnockBack(p2KnockBackDir, p1Acc / totalAcc);

			}
			DrawFormatString(0, 64, 0xffffff, "当たった");

			// このままだと同じ当たり判定を2回繰り返す
			return;
		}
	}
}