#pragma once
#include <iostream>
#include <random>
#include <string>

class Application
{

public:

	//	スクリーンサイズ
	static constexpr int SCREEN_SIZE_X = 1600;
	static constexpr int SCREEN_SIZE_Y = 900;

	//	データパス関連
	//	-------------------------------------------
	static const std::string PATH_IMAGE;
	static const std::string PATH_MODEL;
	static const std::string PATH_EFFECT;
	static const std::string PATH_SOUND;
	static const std::string PATH_SHADER;
	//	-------------------------------------------

	//	明示的にインステンスを生成する
	static void CreateInstance(void);

	//	静的インスタンスの取得
	static Application& GetInstance(void);

	//	初期化
	void Init(void);

	//	ゲームループの開始
	void Run(void);

	//	リソースの破棄
	void Destroy(void);

	//	初期化成功／失敗の判定
	bool IsInitFail(void) const;

	//	解放成功／失敗の判定
	bool IsReleaseFail(void) const;

	int GetRandomNum(int max);
private:

	//	デフォルトコンストラクタをprivateにして、
	//	外部から生成できない様にする
	Application(void);
	Application(const Application& manager) = default;
	~Application(void) = default;

	//	Effekseerの初期化
	void InitEffekseer(void);

	//	静的インスタンス
	static Application* instance_;

	//	初期化失敗
	bool isInitFail_;

	//	解放失敗
	bool isReleaseFail_;

	std::mt19937 gen_;

};
