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
	//�^�C�g���摜
	titleLogoImg_[0] = LoadGraph((Application::PATH_IMAGE + "Title1.png").c_str());
	titleLogoImg_[1] = LoadGraph((Application::PATH_IMAGE + "Title2.png").c_str());

	for (int i = 0; i < TITLE_LOGO_NUM; i++)
	{
		titleLogoPos_[i] = { Application::SCREEN_SIZE_X / 2 , 0 };
		titleLogoShiftTime_[i] = 0;
	}
}

void TitleScene::Update(void)
{
	auto& input = InputManager::GetInstance();

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE) || input.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}

	//�^�C�g�����S�̉����̓���
	if (titleLogoShiftTime_[0] < TITLE_LOGO_UNDER_SHIFT_TIME)
	{
		titleLogoShiftTime_[0]++;
		titleLogoPos_[0].y = SineOut(titleLogoShiftTime_[0]
			, TITLE_LOGO_UNDER_SHIFT_TIME
			, -TITLE_LOGO_SIZE_Y
			, TITLE_LOGO_DEFAULT_POS_Y);
	}
	//�^�C�g�����S�̏㕔�̓���
	if (titleLogoShiftTime_[1] < TITLE_LOGO_TOP_SHIFT_TIME)
	{
		titleLogoShiftTime_[1]++;
		titleLogoPos_[1].y = QuintIn(titleLogoShiftTime_[1]
			, TITLE_LOGO_TOP_SHIFT_TIME
			, -TITLE_LOGO_SIZE_Y
			, TITLE_LOGO_DEFAULT_POS_Y);
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
	//�t�H���g�쐬
	int font;
	font = CreateFontToHandle(NULL, 50, 5);

	DrawFormatString(0, 0, 0xffffff, "Title");

	//�^�C�g�����S
	for (int i = 0; i < TITLE_LOGO_NUM; i++)
	{
		DrawRotaGraph(titleLogoPos_[i].x, titleLogoPos_[i].y, 1.0, 0.0, titleLogoImg_[i], true);
	}

	//push key
	DrawStringToHandle(Application::SCREEN_SIZE_X / 2 - 180
		, Application::SCREEN_SIZE_Y / 2 + 200
		, GetJoypadNum() > 0 ? "Push A Button!!" : "Push Space Key!!"
		, (GetNowCount() / (1000 / 2)) % 2 == 0 ? 0xffffff : 0xbbbbbb
		, font);

	//�t�H���g�폜
	DeleteFontToHandle(font);

}
