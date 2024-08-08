#pragma once

#include<DxLib.h>

class Timer
{
public:

	//定数
	//--------------------

	//カウンター初期化
	static constexpr DATEDATA COUNTER_ZERO = { 0,0,0,0,0,0 };

	//一秒のミリ秒変換
	static constexpr int SEC_2_MILLISEC = 1000;

	//関数
	//--------------------

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//タイマーのリセット
	void ResetTimer(void);

	//シングルトン化
	//--------------------------
	//外部から静的にインスタンスの生成をする
	static void CreateInstance(void);

	//外部でインスタンスを利用可能とするために、
	//インスタンスを返す関数を作る
	static Timer& GetInstance(void);

private:
	//シングルトン化
	//---------------------------

	//コンストラクタ
	Timer(void);
	//デストラクタ
	~Timer(void);

	//コピーコンストラクタを利用できないようにする
	Timer(const Timer& ins);

	//インスタンスの破棄
	void Destroy(void);

	//メンバー変数
	//--------------------------
	//静的なインスタンス格納領域
	static Timer* instance_;

	//経過時間	
	DATEDATA counter_;

	//現在時刻
	int nowCount_;
};