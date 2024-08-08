#include <DxLib.h>      //DX���C�u�����̎g�p����

#include "../../Application.h"


#include "Stage.h"



Stage* Stage::instance_ = nullptr;

//�V���O���g����
void Stage::CreateInstance(void)
{
	//�C���X�^���X��nullptr�Ȃ珉�������ꂽ�̂������������s��

	if (instance_ == nullptr)
	{
		instance_ = new Stage();
	}
	instance_->Init();
}

Stage& Stage::GetInstance(void)
{
	return*instance_;
}

void Stage::Destory(void)
{
	Release();

	delete instance_;
	instance_ = nullptr;
}


//	�R���X�g���N�^
Stage::Stage(void)
{

}

//	�f�X�g���N�^
Stage::~Stage(void)
{

}

void Stage::Init(void)
{
	// �R�c���f���̓ǂݍ���
	ModelHandle = MV1LoadModel((Application::PATH_MODEL+"stage.mv1").c_str());

	// ��ʂɉf��ʒu�ɂR�c���f�����ړ�
	MV1SetPosition(ModelHandle, VGet(0.0f, 00.0f, 550.0f));
	
}

void Stage::Update(void)
{

}

void Stage::Draw(void)
{
	// �R�c���f���̕`��
	MV1DrawModel(ModelHandle);
}

void Stage::Release(void)
{
    // ���f���n���h���̍폜
	MV1DeleteModel(ModelHandle);
}
