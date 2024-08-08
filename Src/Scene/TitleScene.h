#pragma once
#include "SceneBase.h"
#include "../Object/Common/Transform.h"
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
	void Draw(void) override;

private:


};
