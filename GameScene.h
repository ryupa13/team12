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
	const int AnimationSpeed = 12;
	const int HorizonSheet = 6;
	const int VerticalSheet = 1;
	int _animFrameCount;
	Vector2 _offset;
	Vector2 _velocity;
	int count;
};