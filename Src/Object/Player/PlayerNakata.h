#pragma once
#include "../ActorBase.h"

//	���łɐ�l��Player��GameScene�ɃN���X��������肵�Ă����̂ŁA���̈╨�𗘗p���邽�߂ɖ��O��Player�ɂ���
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

