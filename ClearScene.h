#pragma once
#include "BaseScene.h"

//�Q�[���N���A�V�[��
class ClearScene : public BaseScene
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
	int _clearImage;
	int _squareImage;
	int _frameImage;

	//�J�[�\���ԍ�
	int _cursorNumber;
};