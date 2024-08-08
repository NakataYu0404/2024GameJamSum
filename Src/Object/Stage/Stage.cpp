#include <DxLib.h>      //DXライブラリの使用する

#include "Stage.h"



Stage* Stage::instance_ = nullptr;

//シングルトン化
void Stage::CreateInstance(void)
{
	//インスタンスがnullptrなら初期化されたのち生成処理を行う

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


//	コンストラクタ
Stage::Stage(void)
{

}

//	デストラクタ
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