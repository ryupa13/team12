#pragma once
#include "BaseScene.h"
#include "GameObject.h"

//ゲーム画面シーン
class GameScene :public BaseScene
{
public:
	//初期化
	void Initialize();

	//更新
	void Update();

	//解放
	void Release();
private:
	//ゲームの背景画像
	int _gameImage;
	GameObject* _player;
	GameObject* _sumi;
};