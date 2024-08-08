#pragma once
class ResourceManager;

class SceneBase
{

public:

	//	コンストラクタ
	SceneBase(void);

	//	デストラクタ
	virtual ~SceneBase(void) = 0;

	//	初期化処理
	virtual void Init(void) = 0;

	//	更新ステップ
	virtual void Update(void) = 0;

	//	描画処理
	virtual void Draw(void);

protected:

	virtual void Draw3D(void) = 0;
	virtual void Draw2D(void) = 0;
	virtual void DrawUI(void) = 0;

	//	リソース管理
	ResourceManager& resMng_;

};
