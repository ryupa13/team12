#pragma once
#include "BaseScene.h"

//ステージ選択シーン
class StageSelectScene : public BaseScene
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
	int _selectImage;
	int _squareImage;
	int _frameImage;

	//ステージ番号
	int _stageNumber;

	//ステージ番号上限
	int _stageNumberLimit;

	int _gamesceneSE;
	int _gameEXsceneSE;
	int _crr;
};