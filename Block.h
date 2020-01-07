#pragma once
#include "GameObject.h"
#include "Player.h"

//�u���b�N�N���X
class Block : public GameObject
{
public:
	//�R���X�g���N�^
	Block() {}
	Block(Vector2 position) { _position = position; }

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
};