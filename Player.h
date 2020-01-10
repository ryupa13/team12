#pragma once
#include "Vector2.h"
#include "GameObject.h"

//	�v���C���[�N���X
//	��GameObject�N���X���p������
class Player : public GameObject
{
public:
	//	�J�n
	//	��override�C���q���g�p���邱�Ƃ�
	//	���̃����o�֐������N���X�ɑ��݂��Ȃ��ꍇ�A�G���[���o�͂���
	void Start() override;

	//	�`��
	void Render()  override;

	//	�X�V
	void Update()  override;

	//�@���
	void Release()  override;

	//�@�q�b�g�ʒm
	void Hit() override;
	void Hit(GameObject *hitObject) override;
	void Hit(bool hitX, bool hitY) override;

	//�@
	void UpdatePosition(bool hitX, bool hitY);

public:
	//	�摜�n���h��
	int _grp;
};