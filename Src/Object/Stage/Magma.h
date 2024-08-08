#pragma once
#include "../ActorBase.h"


class Magma : public ActorBase
{
public:
	Magma();
	~Magma();

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetParam(void) override;

private:

};

