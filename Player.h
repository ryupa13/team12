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

	// ���
	void Release()  override;

	//�ǂɂԂ����Ă��邩�̔���
	void UpdatePosition(bool hitX, bool hitY);

	//	���x���擾
	Vector2 Velocity() {
		return _velocity;
	}
public:
	//	�摜�n���h��
	int _grp;

	Vector2 _velocity;

	//�s������J�E���g
	int StateCount;
	bool HitWallX;//���ǂɂԂ��������H
	bool HitWallY;//�c�ǂɂԂ��������H
	int rnd;//�����_���i�[�p�ϐ�
};