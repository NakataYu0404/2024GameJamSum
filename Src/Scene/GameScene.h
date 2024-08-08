#pragma once
#include <memory>
#include <vector>
#include "../Object/Common/Transform.h"
#include "SceneBase.h"

class SceneManager;
class AnimationController;

class Stage;
class Magma;

class Player;

using namespace std;

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
	//void Draw(void) override;

private:

	void UpdateReady(void);
	void UpdateInGame(void);
	void UpdateOver(void);

	void Draw3D(void) override;
	void Draw2D(void) override;
	void DrawUI(void) override;


	//	今、ゲームシーン内のどこか
	InSceneType inTypeGame_;

	std::shared_ptr<Stage> stage_;
	std::shared_ptr<Magma> magma_;

	std::vector<shared_ptr<Player>> players_;

	////	折角用意したCollisionManagerを無視してゲームシーンに書かないで下さい。
	//	void Collision();
};
