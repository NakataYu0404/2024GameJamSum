#pragma once
#include <memory>
#include <vector>
#include "../Object/Common/Transform.h"
#include "SceneBase.h"

class SceneManager;
class CollisionManager;
class AnimationController;

class Stage;
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

	static constexpr int PLAYERNUM_MAX = 4;

	//	�R���X�g���N�^
	GameScene(void);

	//	�f�X�g���N�^
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


	//	���A�Q�[���V�[�����̂ǂ���
	InSceneType inTypeGame_;

	std::shared_ptr<Stage> stage_;
	std::shared_ptr<Magma> magma_;

	std::vector<shared_ptr<Player>> players_;

	//	�V���O���g���Q��
	CollisionManager& colMng_;

	//�v���C���[�̏����t���O
	bool player1ReadyFlag_;
	bool player2ReadyFlag_;
	bool player3ReadyFlag_;
	bool player4ReadyFlag_;

	int imgAlready_;
	int imgReady_;

	////	�܊p�p�ӂ���CollisionManager�𖳎����ăQ�[���V�[���ɏ����Ȃ��ŉ������B
	//	void Collision();
};
