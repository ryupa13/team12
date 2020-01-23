#pragma once
#include "BaseScene.h"

//ゲームオーバーシーン
class GameOverScene : public BaseScene
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
	int _gameoverImage;
	int _squareImage;
	int _frameImage;

	//カーソル番号
	int _cursorNumber;

	int _gameoverSE;
	int _cl;
};