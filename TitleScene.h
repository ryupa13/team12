#pragma once
#include "BaseScene.h"

//�^�C�g����ʃV�[��
class TitleScene : public BaseScene
{
public:
	//������
	void Initialize();

	//�X�V
	void Update();

	//���
	void Release();
private:
	//�^�C�g���̔w�i�摜
	int _titleImage;
	int _frameImage;

	//SE
	int _titleSE;

	//�J�[�\���ԍ�
	int _cursorNumber;
};