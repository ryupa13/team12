#pragma once
#include "BaseScene.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"

//�Q�[����ʃV�[��
class GameScene :public BaseScene
{
public:
	//������
	void Initialize();

	//�X�V
	void Update();

	//���
	void Release();
private:
	//�Q�[���̔w�i�摜
	int _gameImage;
	TileMap _tileMap;
	Player _player;
	Enemy _enemy;
};