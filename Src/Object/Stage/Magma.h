#pragma once
#include <memory>
#include "../ActorBase.h"

class EffectController;

class Magma : public ActorBase
{
public:

	enum class EFFECT_TYPE
	{
		MAGMA_BUBBLE,
		MAGMA_JUMP,
	};

	Magma();
	~Magma();

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetParam(void) override;


private:

	std::shared_ptr<EffectController> effectController_;
};

