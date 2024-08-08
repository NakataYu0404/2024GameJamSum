#pragma once
#include "../ActorBase.h"

//	すでに先人がPlayerでGameSceneにクラスを作ったりしていたので、その遺物を利用するために名前をPlayerにした
class Player : public ActorBase
{
public:

	Player();
	~Player();

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetParam(void) override;

private:



};

