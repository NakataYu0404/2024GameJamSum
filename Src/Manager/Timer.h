#pragma once

#include<DxLib.h>
#include"../Common/Vector2.h"

class Timer
{
public:

	//�萔
	//--------------------

	//�J�E���^�[������
	static constexpr DATEDATA COUNTER_ZERO = { 0,0,0,0,0,0 };

	//��������
	static constexpr DATEDATA TIME_LIMIT = { 0,0,0,0,0,60 };

	//��b�̃~���b�ϊ�
	static constexpr int SEC_2_MILLISEC = 1000;

	//�摜�֌W
	//--------------------

	//�^�C�}�[�t���[���̑傫��
	static constexpr int FRAME_SIZE_X = 200;
	static constexpr int FRAME_SIZE_Y = 80;

	//�t���[���̍��W�����炷
	static constexpr int FRAME_SHIFT_POS_Y = 10;

	//�����摜�T�C�Y
	static constexpr int NUMBER_SIZE_X = 50;
	static constexpr int NUMBER_SIZE_Y = 80;

	//�����摜�̕�����
	static constexpr int NUMBER_X_DIV = 10;
	static constexpr int NUMBER_Y_DIV = 1;
	static constexpr int NUMBER_ALL_DIV = NUMBER_X_DIV * NUMBER_Y_DIV;

	//�֐�
	//--------------------

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//�^�C�}�[�̃��Z�b�g
	void ResetTimer(void);

	//�������Ԓ��ߔ����Ԃ�
	bool IsTimeOver(void);

	//�V���O���g����
	//--------------------------
	//�O������ÓI�ɃC���X�^���X�̐���������
	static void CreateInstance(void);

	//�O���ŃC���X�^���X�𗘗p�\�Ƃ��邽�߂ɁA
	//�C���X�^���X��Ԃ��֐������
	static Timer& GetInstance(void);

	//�C���X�^���X�̔j��
	void Destroy(void);

private:
	//�V���O���g����
	//---------------------------

	//�R���X�g���N�^
	Timer(void);
	//�f�X�g���N�^
	~Timer(void);

	//�R�s�[�R���X�g���N�^�𗘗p�ł��Ȃ��悤�ɂ���
	Timer(const Timer& ins);

	//�����o�[�ϐ�
	//--------------------------
	//�ÓI�ȃC���X�^���X�i�[�̈�
	static Timer* instance_;

	//�o�ߎ���	
	DATEDATA counter_;

	//���ݎ���
	int nowCount_;

	//�^�C�}�[�t���[���̉摜
	int timerFrameImg_;

	//�^�C�}�[�t���[���̍��W
	Vector2 framePos_;

	//�����̉摜
	int numberImg_[10];
};