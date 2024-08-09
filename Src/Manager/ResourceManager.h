#pragma once
#include <map>
#include <string>
#include "Resource.h"

class ResourceManager
{

public:

	//	���\�[�X��
	enum class SRC
	{
		//	�摜 IMG_����n�߂邱��
		//	��FIMG_TITLE
		IMG_READY,
		IMG_ALREADY,
		IMG_WIN,
		IMG_PLAYER1,
		IMG_PLAYER2,
		IMG_PLAYER3,
		IMG_PLAYER4,

		//	���f�� MDL_
		MDL_NONE,
		MDL_STAGE,
		MDL_ROCK,
		MDL_MAGMA,

		MDL_PLAYER_BALL1,
		MDL_PLAYER_BALL2,
		MDL_PLAYER_BALL3,
		MDL_PLAYER_BALL4,

		MDL_PLAYER_RED,
		MDL_PLAYER_GREEN,
		MDL_PLAYER_BLUE,
		MDL_PLAYER_YELLOW,

		//	�G�t�F�N�g EFF_
		EFF_MAGMA_JUMP,
		EFF_MAGMA_BUBBLE,
		EFF_HITBODY,

		//	�T�E���h SND_
		SND_WIN,
		SND_GAME_START,
		SND_GAME_END,
		SND_DECIDE,
		SND_ROLL_1,
		SND_ROLL_2,
		SND_ROLL_3,
		SND_ROLL_4,
		SND_BGM,


	};

	//	�����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	//	�ÓI�C���X�^���X�̎擾
	static ResourceManager& GetInstance(void);

	//	������
	void Init(void);

	//	���(�V�[���ؑ֎��Ɉ�U���)
	void Release(void);

	//	���\�[�X�̊��S�j��
	void Destroy(void);

	//	���\�[�X�̃��[�h
	const Resource& Load(SRC src);

	//	���\�[�X�̕������[�h(���f���p)
	int LoadModelDuplicate(SRC src);

private:

	//	�ÓI�C���X�^���X
	static ResourceManager* instance_;

	//	���\�[�X�Ǘ��̑Ώ�
	std::map<SRC, Resource*> resourcesMap_;

	//	�ǂݍ��ݍς݃��\�[�X
	std::map<SRC, Resource&> loadedMap_;

	Resource dummy_;

	//	�f�t�H���g�R���X�g���N�^��private�ɂ��āA
	//	�O�����琶���ł��Ȃ��l�ɂ���
	ResourceManager(void);
	ResourceManager(const ResourceManager& manager) = default;
	~ResourceManager(void) = default;

	//	�������[�h
	Resource& _Load(SRC src);

};
