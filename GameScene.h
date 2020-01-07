#pragma once
#include "BaseScene.h"
#include "TileMap.h"
#include "GameObject.h"

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
	GameObject* _player;
};