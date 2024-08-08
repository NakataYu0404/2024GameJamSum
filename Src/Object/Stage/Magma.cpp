#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../Common/EffectController.h"
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
	effectController_ = std::make_shared<EffectController>();

	auto& resIns = resMng_.GetInstance();

	transform_->SetModel(resIns.LoadModelDuplicate(ResourceManager::SRC::MDL_MAGMA));

	effectController_->Add((int)EFFECT_TYPE::MAGMA_JUMP, resIns.Load(ResourceManager::SRC::EFF_MAGMAJUMP).handleId_);
	effectController_->Add((int)EFFECT_TYPE::MAGMA_BUBBLE, resIns.Load(ResourceManager::SRC::EFF_MAGMABUBBLE).handleId_);

	SetParam();
}

void Magma::Update(void)
{
	//effectController_->Play()
}

void Magma::Draw(void)
{
	MV1DrawModel(transform_->modelId);
}

void Magma::SetParam(void)
{
	transform_->pos = { 0.0f,-1000.0f,1000.0f };
	transform_->quaRot = Quaternion();
	transform_->scl = { 1.0f,1.0f,1.0f };

	transform_->Update();
}
