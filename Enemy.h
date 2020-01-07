#pragma once
#include "GameObject.h"
#include "Player.h"

//�G�l�~�[�N���X
class Enemy : public GameObject
{
public:
	//�R���X�g���N�^
	Enemy() {}
	Enemy(Vector2 position) { _position = position; }

	//�J�n
	void Start() override;

	//�`��
	void Render() override;

	//�X�V
	void Update() override;

	//�q�b�g�ʒm
	void Hit() override;
	void Hit(bool hitX, bool hitY) override;

	//���
	void Release() override;

public:
	//�摜�n���h��
	int _grp;
	//�v���C���[���W
	Vector2 _playerPosition;
	//�v���C���[���m�͈�
	float _searchPlayerRadius;
	//�n���m�͈�
	float _searchInkRadius;
	//�ړ���
	Vector2 _velocity;
};