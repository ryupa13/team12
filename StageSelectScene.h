#pragma once
#include "BaseScene.h"

//�X�e�[�W�I���V�[��
class StageSelectScene : public BaseScene
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
	int _selectImage;
	int _squareImage;
	int _frameImage;

	//�X�e�[�W�ԍ�
	int _stageNumber;

	//�X�e�[�W�ԍ����
	int _stageNumberLimit;

	int _gamesceneSE;
	int _gameEXsceneSE;
	int _crr;
};