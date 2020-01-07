#pragma once
#include "BaseScene.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"

//ƒQ[ƒ€‰æ–ÊƒV[ƒ“
class GameScene :public BaseScene
{
public:
	//‰Šú‰»
	void Initialize();

	//XV
	void Update();

	//‰ğ•ú
	void Release();
private:
	//ƒQ[ƒ€‚Ì”wŒi‰æ‘œ
	int _gameImage;
	TileMap _tileMap;
	Player _player;
	Enemy _enemy;
};