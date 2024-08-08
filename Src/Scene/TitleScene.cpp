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
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	
}

void TitleScene::Update(void)
{
	//TODO ゲームパッドのAボタンの判定の追加
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}

void TitleScene::Draw(void)
{
	int font;

	font = CreateFontToHandle(NULL, 50, 5);

	DrawFormatString(0, 0, 0xffffff, "Title");

	Stage::GetInstance().Draw();

	DrawStringToHandle(Application::SCREEN_SIZE_X / 2 - 180
		, Application::SCREEN_SIZE_Y / 2 + 200
		, GetJoypadNum() > 0 ? "Push A Button!!" : "Push Space Key!!"
		, (GetNowCount() / (1000 / 2)) % 2 == 0 ? 0xffffff : 0xbbbbbb
		, font);

	DeleteFontToHandle(font);
}
