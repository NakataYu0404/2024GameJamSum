#pragma once
#include "SceneBase.h"
#include "../Object/Common/Transform.h"
#include"../Common/Vector2.h"
class SceneManager;
class AnimationController;


class TitleScene : public SceneBase
{

public:

	//	�R���X�g���N�^
	TitleScene(void);

	//	�f�X�g���N�^
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	//void Draw(void) override;

private:
	//�^�C�g�����S�̑傫��
	static constexpr int TITLE_LOGO_SIZE_X = 800;
	static constexpr int TITLE_LOGO_SIZE_Y = 400;

	//�^�C�g�����S�̍��v��
	static constexpr int TITLE_LOGO_NUM = 3;

	//�^�C�g�����S�̊�{�ʒu
	static constexpr int TITLE_LOGO_DEFAULT_POS_Y = 300;

	//�^�C�g�����S�̈ړ�����
	static constexpr float TITLE_LOGO_UNDER_SHIFT_TIME = 60.0f * 2.0f;
	static constexpr float TITLE_LOGO_TOP_SHIFT_TIME = 60.0f * 3.0f;
	static constexpr float TITLE_LOGO_BACK_SHIFT_TIME = 60.0f * 1.0f;

	void Draw3D(void) override;
	void Draw2D(void) override;
	void DrawUI(void) override;

	//�^�C�g�����S
	int titleLogoImg_[TITLE_LOGO_NUM];

	//�^�C�g�����S�̍��W
	Vector2 titleLogoPos_[TITLE_LOGO_NUM];

	//�^�C�g�����S�̈ړ�����
	int titleLogoShiftTime_[TITLE_LOGO_NUM];

	//�^�C�g�����S�̔w�i�̑傫���p
	float titleLogoBackScale_[TITLE_LOGO_NUM];
};
