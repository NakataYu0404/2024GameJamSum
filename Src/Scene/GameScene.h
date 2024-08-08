#pragma once
#include "SceneBase.h"
#include "../Object/Common/Transform.h"
class SceneManager;
class AnimationController;
class Magma;

class GameScene : public SceneBase
{

public:

	//	ゲームシーン内のシーン
	enum class InSceneType
	{
		//	ゲーム開始前シーン
		READY,

		//	ゲーム中シーン
		INGAME,

		//	ゲーム終了演出シーン
		GAMEOVER,
	};

	//	コンストラクタ
	GameScene(void);

	//	デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	void UpdateReady(void);
	void UpdateInGame(void);
	void UpdateOver(void);

	void Draw3D(void);
	void Draw2D(void);
	void DrawUI(void);


	//	今、ゲームシーン内のどこか
	InSceneType inTypeGame_;

	std::shared_ptr<Magma> magma_;
};
