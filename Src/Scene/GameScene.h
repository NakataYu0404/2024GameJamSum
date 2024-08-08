#pragma once
#include "SceneBase.h"
#include "../Object/Common/Transform.h"
class SceneManager;
class AnimationController;


class GameScene : public SceneBase
{

public:

	//	�R���X�g���N�^
	GameScene(void);

	//	�f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:


};
