#include <memory>
#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/Timer.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include "../Object/Common/AnimationController.h"
#include "../Object/Stage/Magma.h"
#include "../Object/Stage/Stage.h"
#include "GameScene.h"

//#include "../Object/Player.h"
//#include "../Object/Player1.h"
//#include "../Object/Player2.h"

#include "../Object/Player/PlayerNakata.h"

#include "../Object/Common/CollisionManager.h"
#include "../Object/Common/Sphere.h"

GameScene::GameScene(void) : colMng_(CollisionManager::GetInstance())
{
	//	プレイヤーを複数実装する場合、Playerのコンストラクタ等でプレイヤー番号を渡せば別クラスを作る必要がありません。機能も同じですし。
	//	プレイヤー毎の初期座標はPlayer1,2でなく結局Playerのコンストラクタで決めている所を見るに完全な冗長であると思います。
	////players_.push_back(make_shared<Player1>());
	////VECTOR initPos = { 300.0f,0.0f,0.0f };
	////players_.push_back(make_shared<Player2>(initPos));
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	colMng_.Init();

	inTypeGame_ = InSceneType::READY;
	for (int i = 0; i < PLAYERNUM_MAX; i++)
	{
		players_.push_back(make_shared<Player>(i));
	}
	for (auto& p : players_)
	{
		p->Init();
		colMng_.Add(p);
	}

	for (auto& p : players_)
	{
		for (auto& a : players_)
		{
			p->SetPlayers(a);
		}
	}

	stage_ = std::make_shared<Stage>();
	stage_->Init();

	colMng_.Add(stage_);

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

}

//void GameScene::Draw(void)
//{
//
//	//	3Dを描画
//	Draw3D();
//
//	//	2Dを描画
//	Draw2D();
//
//	//	UIを描画
//	DrawUI();
//
////	なぜここでCollision関数が呼ばれるのか流石に理解できません
////	Collision();
//}

void GameScene::Draw3D(void)
{
	//	3Dのもの描画
	stage_->Draw();
	magma_->Draw();

	for (auto& p : players_) 
	{
		p->Draw();
	}

}

void GameScene::Draw2D(void)
{
	//	3D上に描画したい2Dのもの描画

}

void GameScene::DrawUI(void)
{
	//	UI描画
	switch (inTypeGame_)
	{
	case GameScene::InSceneType::READY:
		break;
	case GameScene::InSceneType::INGAME:
		Timer::GetInstance().Draw();
		break;
	case GameScene::InSceneType::GAMEOVER:
		break;
	default:
		break;
	}

	DrawFormatString(0, 0, 0xffffff, "Game");

}

void GameScene::UpdateReady(void)
{
	auto& input = InputManager::GetInstance();

	if (input.IsTrgDown(KEY_INPUT_SPACE) ||
		(input.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1,InputManager::JOYPAD_BTN::DOWN)&&
		input.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD2, InputManager::JOYPAD_BTN::DOWN)&&
		input.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD3, InputManager::JOYPAD_BTN::DOWN)&&
		input.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD4, InputManager::JOYPAD_BTN::DOWN)))
	{
		//	TODO:ここにカウントダウン演出を追加して、カウントダウンが終わったらinTypeGameが変わるようにする
		inTypeGame_ = InSceneType::INGAME;
		Timer::GetInstance().ResetTimer();
	}
}

void GameScene::UpdateInGame(void)
{
	magma_->Update();

	for (auto& p : players_)
	{
		p->Update();
	}

	colMng_.Update();


	//	if(決着)
	//	{	
			if(players_[0]->GetAlive())
	//		if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_NUMPAD0))
	//		{
	//			inTypeGame_ = InSceneType::GAMEOVER;
	//		}
	//	}
}

void GameScene::UpdateOver(void)
{
	auto& input = InputManager::GetInstance();
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE) || input.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}


//void GameScene::Collision()
//{
//	for (auto& p1 : players_) {
//		for (auto& p2 : players_) {
//			if (p1 == p2) continue;
//			// 判定
//			float distance = VSize(VSub(p1->GetTransform().lock()->pos, p2->GetTransform().lock()->pos));
//			float CollDistance = p1->GetSphere().lock()->GetRadius() + p2->GetSphere().lock()->GetRadius();
//			if (distance <= CollDistance) {
//				// 衝突判定
//				VECTOR p1Dir = p1->GetMoveDir();
//				VECTOR p2Dir = p2->GetMoveDir();
//				VECTOR dir = { 0.0f,0.0f,1.0f };
//				//p1->SetMoveDir(dir);
//				// p2->SetMoveDir(p1Dir);
//				// p1->SwitchMoveDir();
//				if (p1->GetMoveAcc() >= p2->GetMoveAcc()) {
//					p1->ProcessKnockBack(VScale(p1Dir, -1), 1.1f);
//				}
//				else{
//					p2->ProcessKnockBack(VScale(p2Dir, -1), 1.1f);
//				}
//				DrawFormatString(0, 64, 0xffffff, "当たった");
//				return;
//			}
//		}
//	}
//}