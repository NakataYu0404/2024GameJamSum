#include <memory>
#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Common/Easing.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include "../Object/Common/AnimationController.h"
#include "../Object/Stage/Stage.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	//タイトル画像
	titleLogoImg_[0] = LoadGraph((Application::PATH_IMAGE + "Title1.png").c_str());
	titleLogoImg_[1] = LoadGraph((Application::PATH_IMAGE + "Title2.png").c_str());

	titleLogoPos_[0] = { Application::SCREEN_SIZE_X / 2 , TITLE_LOGO_DEFAULT_POS_Y };
	titleLogoPos_[1] = { Application::SCREEN_SIZE_X / 2 , 0 };
}

void TitleScene::Update(void)
{
	//TODO ゲームパッドのAボタンの判定の追加
	auto& input = InputManager::GetInstance();

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE) || input.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}

	if (titleLogoShiftTime_ < SceneManager::GetInstance().GetDeltaTime() * 3.0f)
	{
		titleLogoShiftTime_++;
		//TODO タイトルロゴの動き
		//titleLogoPos_[1] = SineOut(titleLogoShiftTime_
		//	, SceneManager::GetInstance().GetDeltaTime() * 3.0f
		//	,)
	}
}

//void TitleScene::Draw(void)
//{
//}

void TitleScene::Draw3D(void)
{
}

void TitleScene::Draw2D(void)
{
}

void TitleScene::DrawUI(void)
{
	//フォント作成
	int font;
	font = CreateFontToHandle(NULL, 50, 5);

	DrawFormatString(0, 0, 0xffffff, "Title");

	//タイトルロゴ
	for (int i = 0; i < TITLE_LOGO_NUM; i++)
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 300, 1.0, 0.0, titleLogoImg_[i], true);
	}

	//push key
	DrawStringToHandle(Application::SCREEN_SIZE_X / 2 - 180
		, Application::SCREEN_SIZE_Y / 2 + 200
		, GetJoypadNum() > 0 ? "Push A Button!!" : "Push Space Key!!"
		, (GetNowCount() / (1000 / 2)) % 2 == 0 ? 0xffffff : 0xbbbbbb
		, font);

	//フォント削除
	DeleteFontToHandle(font);

}
