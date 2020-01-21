#pragma once
#include "BaseScene.h"

//ゲームクリアシーン
class ClearScene : public BaseScene
{
public:
	//初期化
	void Initialize();

	//更新
	void Update();

	//解放
	void Release();

private:
	//画像のハンドル
	int _clearImage;
	int _squareImage;
	int _frameImage;

	//カーソル番号
	int _cursorNumber;
};