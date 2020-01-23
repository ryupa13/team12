#pragma once
#include "BaseScene.h"

//�Q�[���I�[�o�[�V�[��
class GameOverScene : public BaseScene
{
public:
	//������
	void Initialize();

	//�X�V
	void Update();

	//���
	void Release();

private:
	//�摜�̃n���h��
	int _gameoverImage;
	int _squareImage;
	int _frameImage;

	//�J�[�\���ԍ�
	int _cursorNumber;

	int _gameoverSE;
	int _cl;
};