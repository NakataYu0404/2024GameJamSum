#pragma once
#include "SceneBase.h"
#include "../Object/Common/Transform.h"
#include"../Common/Vector2.h"
class SceneManager;
class AnimationController;


class TitleScene : public SceneBase
{

public:

	//	コンストラクタ
	TitleScene(void);

	//	デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	//void Draw(void) override;

private:
	//タイトルロゴの大きさ
	static constexpr int TITLE_LOGO_SIZE_X = 800;
	static constexpr int TITLE_LOGO_SIZE_Y = 400;

	//タイトルロゴの合計数
	static constexpr int TITLE_LOGO_NUM = 2;

	//タイトルロゴの基本位置
	static constexpr int TITLE_LOGO_DEFAULT_POS_Y = 300;

	void Draw3D(void) override;
	void Draw2D(void) override;
	void DrawUI(void) override;

	//タイトルロゴ
	int titleLogoImg_[TITLE_LOGO_NUM];

	//タイトルロゴの座標
	Vector2 titleLogoPos_[TITLE_LOGO_NUM];

	//タイトルロゴの移動時間
	int titleLogoShiftTime_;
};
