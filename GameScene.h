#pragma once
#include "BaseScene.h"
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
	GameObject* _player;
	GameObject* _sumi;
};