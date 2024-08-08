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
}

void GameScene::UpdateReady(void)
{
	//	if(èÄîıäÆóπ)
	//	{
	//		inTypeGame_ = InSceneType::INGAME;
	//	}
}

void GameScene::UpdateInGame(void)
{
	//	if(åàíÖ)
	//	{
	//		inTypeGame_ = InSceneType::GAMEOVER;
	//	}
}

void GameScene::UpdateOver(void)
{
}
