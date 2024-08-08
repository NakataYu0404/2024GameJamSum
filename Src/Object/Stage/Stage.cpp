#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../Common/CollisionManager.h"
#include "../Common/Collider.h"
#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Init(void)
{
	transform_ = std::make_shared<Transform>();

	auto& resIns = resMng_.GetInstance();

	transform_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_STAGE));

	SetParam();

}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	MV1DrawModel(transform_->modelId);
}

void Stage::SetParam(void)
{
	transform_->pos = { 0.0f,0.0f,0.0f };
	transform_->quaRot = Quaternion();
	transform_->scl = { 1.0f,1.0f,1.0f };

	transform_->MakeCollider(Collider::Category::STAGE, Collider::TYPE::MODEL);

	transform_->Update();
}
