#pragma once

//�V�[���̊��N���X
class BaseScene
{
public:
	// () = 0 �ɂ��邱�Ƃŏ������z�֐��ɂȂ���
	//������
	virtual void Initialize() = 0;

	//�X�V
	virtual void Update() = 0;

	//���
	virtual void Release() = 0;
};