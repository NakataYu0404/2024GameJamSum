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

GameScene::GameScene(void)
{
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
}

void GameScene::Draw(void)
{
	DrawFormatString(0, 0, 0xffffff, "Game");

	Draw3D();
	Draw2D();
	DrawUI();
}

void GameScene::UpdateReady(void)
{
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_NUMPAD0))
	{
		inTypeGame_ = InSceneType::INGAME;
		Timer::GetInstance().ResetTimer();
	}
}

void GameScene::UpdateInGame(void)
{
	magma_->Update();

	//	if(åàíÖ)
	//	{
	//		inTypeGame_ = InSceneType::GAMEOVER;
	//	}
}

void GameScene::UpdateOver(void)
{

}

void GameScene::Draw3D(void)
{
	//	3DÇÃÇ‡ÇÃï`âÊ
	//Stage::GetInstance().Draw();

	magma_->Draw();
}

void GameScene::Draw2D(void)
{
	//	3Dè„Ç…ï`âÊÇµÇΩÇ¢2DÇÃÇ‡ÇÃï`âÊ

}

void GameScene::DrawUI(void)
{
	//	UIï`âÊ
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



}
