#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../Common/EffectController.h"
#include "MagmaEffects.h"
#include "Magma.h"

Magma::Magma()
{
}

Magma::~Magma()
{
}

void Magma::Init(void)
{
	transform_ = std::make_shared<Transform>();

	auto& resIns = resMng_.GetInstance();

	transform_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_MAGMA));

	SetParam();

	VECTOR pos = transform_->pos;

	magmaEffects_.push_back(std::make_shared<MagmaEffects>(pos));
	for (auto m : magmaEffects_)
	{
		m->Init();
	}

}

void Magma::Update(void)
{
	for (auto m : magmaEffects_)
	{
		m->Update();
	}
}

void Magma::Draw(void)
{
	MV1DrawModel(transform_->modelId);
}

void Magma::SetParam(void)
{
	transform_->pos = { 0.0f,-200.0f,1500.0f };
	transform_->quaRot = Quaternion();
	transform_->scl = { 1.4f,1.0f,1.4f };

	transform_->Update();
}
