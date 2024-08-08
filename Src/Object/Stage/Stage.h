#pragma once

#include <memory>


class Stage
{

public:

	
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
		
	//インスタンスの生成
	//シングルトン化
	static void CreateInstance(void);

	static Stage& GetInstance(void);

private:

	int ModelHandle;

	//シングルトン化
	static Stage* instance_;

	//メンバー関数
	//------------
	//デフォルトコンストラクタ
	Stage(void);

	//デストラクタ
	~Stage(void);

	//コピーコンストラスタ
	Stage(const Stage& ins);

	void Destory(void);

};

