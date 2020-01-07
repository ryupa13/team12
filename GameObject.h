#pragma once
#include "Vector2.h"

//	�Q�[���I�u�W�F�N�g�N���X
class GameObject
{
public:
	//	�R���X�g���N�^
	GameObject() : _position(0, 0), _size(0, 0) {}

	//	�J�n
	virtual void Start() = 0;

	//	�`��
	virtual void Render() = 0;

	//	�X�V
	virtual void Update() = 0;

	//	���
	virtual void Release() = 0;

	//	��Tips�����o�֐���const��t�^���鎖��
	//	���̊֐����ł̃����o�ϐ��̕ύX���֎~�ɂ���
	Vector2 Position() const { return _position; }
	Vector2 Size() const { return _size; }
	float Radius() const { return _radius; }

public:
	Vector2 _position;		//	���W
	Vector2 _size;			//	�T�C�Y
	float _radius;			//	���a
};