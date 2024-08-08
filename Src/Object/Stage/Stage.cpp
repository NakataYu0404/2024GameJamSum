#include <DxLib.h>      //DXライブラリの使用する

#include "../../Application.h"


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
	Release();

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
	// ３Ｄモデルの読み込み
	ModelHandle = MV1LoadModel((Application::PATH_MODEL+"stage.mv1").c_str());

	// 画面に映る位置に３Ｄモデルを移動
	MV1SetPosition(ModelHandle, VGet(0.0f, 00.0f, 550.0f));
	
}

void Stage::Update(void)
{

}

void Stage::Draw(void)
{
	// ３Ｄモデルの描画
	MV1DrawModel(ModelHandle);
}

void Stage::Release(void)
{
    // モデルハンドルの削除
	MV1DeleteModel(ModelHandle);
}
