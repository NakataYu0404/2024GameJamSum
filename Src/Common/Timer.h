#pragma once

#include<DxLib.h>

class Timer
{
public:

	//�萔
	//--------------------

	//�J�E���^�[������
	static constexpr DATEDATA COUNTER_ZERO = { 0,0,0,0,0,0 };

	//��b�̃~���b�ϊ�
	static constexpr int SEC_2_MILLISEC = 1000;

	//�֐�
	//--------------------

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//�^�C�}�[�̃��Z�b�g
	void ResetTimer(void);

	//�V���O���g����
	//--------------------------
	//�O������ÓI�ɃC���X�^���X�̐���������
	static void CreateInstance(void);

	//�O���ŃC���X�^���X�𗘗p�\�Ƃ��邽�߂ɁA
	//�C���X�^���X��Ԃ��֐������
	static Timer& GetInstance(void);

private:
	//�V���O���g����
	//---------------------------

	//�R���X�g���N�^
	Timer(void);
	//�f�X�g���N�^
	~Timer(void);

	//�R�s�[�R���X�g���N�^�𗘗p�ł��Ȃ��悤�ɂ���
	Timer(const Timer& ins);

	//�C���X�^���X�̔j��
	void Destroy(void);

	//�����o�[�ϐ�
	//--------------------------
	//�ÓI�ȃC���X�^���X�i�[�̈�
	static Timer* instance_;

	//�o�ߎ���	
	DATEDATA counter_;

	//���ݎ���
	int nowCount_;
};