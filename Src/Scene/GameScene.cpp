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
#include "../Object/Common/CollisionManager.h"
#include "../Object/Common/Sphere.h"

GameScene::GameScene(void)
{

	players_.push_back(make_shared<Player>());
	VECTOR initPos = { 300.0f,0.0f,0.0f };
	players_.push_back(make_shared<Player>(initPos));
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
	//	if(€”õŠ®—¹)
	//	{
	//		inTypeGame_ = InSceneType::INGAME;
	//	}
}

void GameScene::UpdateInGame(void)
{
	//	if(Œˆ’…)
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
			// ”»’è
			float distance = VSize(VSub(p1->GetTransform().lock()->pos, p2->GetTransform().lock()->pos));
			float CollDistance = p1->GetSphere().lock()->GetRadius() + p2->GetSphere().lock()->GetRadius();
			if (distance <= CollDistance) {
				// Õ“Ë”»’è
				//VECTOR p1Dir = p1->GetMoveDir();
				//VECTOR p2Dir = p2->GetMoveDir();
				//p1->SetMoveDir(p2Dir);
				//p2->SetMoveDir(p1Dir);
				DrawFormatString(0, 64, 0xffffff, "“–‚½‚Á‚½");
			}
		}
	}
}