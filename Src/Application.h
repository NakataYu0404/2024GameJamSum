#pragma once
#include <iostream>
#include <random>
#include <string>

class Application
{

public:

	//	�X�N���[���T�C�Y
	static constexpr int SCREEN_SIZE_X = 1600;
	static constexpr int SCREEN_SIZE_Y = 900;

	//	�f�[�^�p�X�֘A
	//	-------------------------------------------
	static const std::string PATH_IMAGE;
	static const std::string PATH_MODEL;
	static const std::string PATH_EFFECT;
	static const std::string PATH_SOUND;
	static const std::string PATH_SHADER;
	//	-------------------------------------------

	//	�����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	//	�ÓI�C���X�^���X�̎擾
	static Application& GetInstance(void);

	//	������
	void Init(void);

	//	�Q�[�����[�v�̊J�n
	void Run(void);

	//	���\�[�X�̔j��
	void Destroy(void);

	//	�����������^���s�̔���
	bool IsInitFail(void) const;

	//	��������^���s�̔���
	bool IsReleaseFail(void) const;

	int GetRandomNum(int max);
private:

	//	�f�t�H���g�R���X�g���N�^��private�ɂ��āA
	//	�O�����琶���ł��Ȃ��l�ɂ���
	Application(void);
	Application(const Application& manager) = default;
	~Application(void) = default;

	//	Effekseer�̏�����
	void InitEffekseer(void);

	//	�ÓI�C���X�^���X
	static Application* instance_;

	//	���������s
	bool isInitFail_;

	//	������s
	bool isReleaseFail_;

	std::mt19937 gen_;

};
