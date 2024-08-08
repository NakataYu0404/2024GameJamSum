#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "Magma.h"

Magma::Magma()
{
}

Magma::~Magma()
{
}

void Magma::Init(void)
{
	auto& resIns = resMng_.GetInstance();

	transform_ = std::make_shared<Transform>();

	transform_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_MAGMA));

	SetParam();
}

void Magma::Update(void)
{
}

void Magma::Draw(void)
{
	MV1DrawModel(transform_->modelId);
}

void Magma::SetParam(void)
{
	transform_->pos = { 0.0f,0.0f,0.0f };
	transform_->quaRot = Quaternion();
	transform_->scl = { 1.0f,1.0f,1.0f };

}
