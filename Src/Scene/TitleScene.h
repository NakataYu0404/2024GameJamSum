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
	static constexpr int TITLE_LOGO_NUM = 2;

	//�^�C�g�����S�̊�{�ʒu
	static constexpr int TITLE_LOGO_DEFAULT_POS_Y = 300;

	void Draw3D(void) override;
	void Draw2D(void) override;
	void DrawUI(void) override;

	//�^�C�g�����S
	int titleLogoImg_[TITLE_LOGO_NUM];

	//�^�C�g�����S�̍��W
	Vector2 titleLogoPos_[TITLE_LOGO_NUM];

	//�^�C�g�����S�̈ړ�����
	int titleLogoShiftTime_;
};
