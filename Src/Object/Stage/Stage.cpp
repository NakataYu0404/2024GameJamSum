#include <DxLib.h>      //DX���C�u�����̎g�p����

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

}

void Stage::Update(void)
{

}

void Stage::Draw(void)
{

}