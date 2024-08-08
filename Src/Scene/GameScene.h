#pragma once
#include "SceneBase.h"
#include "../Object/Common/Transform.h"
#include <memory>

class SceneManager;
class AnimationController;
class Magma;

class Player;

using namespace std;

class GameScene : public SceneBase
{

public:

	//	�Q�[���V�[�����̃V�[��
	enum class InSceneType
	{
		//	�Q�[���J�n�O�V�[��
		READY,

		//	�Q�[�����V�[��
		INGAME,

		//	�Q�[���I�����o�V�[��
		GAMEOVER,
	};

	//	�R���X�g���N�^
	GameScene(void);

	//	�f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	void UpdateReady(void);
	void UpdateInGame(void);
	void UpdateOver(void);

	//	���A�Q�[���V�[�����̂ǂ���
	InSceneType inTypeGame_;

	std::shared_ptr<Magma> magma_;

	vector <shared_ptr<Player>> players_;
	void Collision();
};
