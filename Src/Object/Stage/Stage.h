#pragma once

#include <memory>


class Stage
{

public:

	
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
		
	//�C���X�^���X�̐���
	//�V���O���g����
	static void CreateInstance(void);

	static Stage& GetInstance(void);

private:

	int ModelHandle;

	//�V���O���g����
	static Stage* instance_;

	//�����o�[�֐�
	//------------
	//�f�t�H���g�R���X�g���N�^
	Stage(void);

	//�f�X�g���N�^
	~Stage(void);

	//�R�s�[�R���X�g���X�^
	Stage(const Stage& ins);

	void Destory(void);

};

