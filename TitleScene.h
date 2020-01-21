#pragma once
#include "BaseScene.h"

//タイトル画面シーン
class TitleScene : public BaseScene
{
public:
	//初期化
	void Initialize();

	//更新
	void Update();

	//解放
	void Release();
private:
	//タイトルの背景画像
	int _titleImage;

	//SE
	int _titleSE;
};