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

	//�@�q�b�g�ʒm
	virtual void Hit() = 0;
	virtual void Hit(GameObject *hitObject) = 0;
	virtual void Hit(bool hitX, bool hitY) = 0;

	//	���
	virtual void Release() = 0;

	//	��Tips�����o�֐���const��t�^���鎖��
	//	���̊֐����ł̃����o�ϐ��̕ύX���֎~�ɂ���
	Vector2 Position() const { return _position; }
	Vector2 Size() const { return _size; }
	Vector2 Velocity() const { return _velocity; }
	float Radius() const { return _radius; }
	bool IsDead() const
	{
		if (_state == State::Dead)
			return true;
		return false;
	}
	bool IsClear() const
	{
		if (_state == State::Clear)
			return true;
		return false;
	}

public:
	Vector2 _position;		//	���W
	Vector2 _size;			//	�T�C�Y
	Vector2 _rectSize;
	Vector2 _rectPosition; //�؂蔲���n�߂�ʒu
	float _radius;			//	���a
	Vector2 _velocity;
	enum State
	{
		Alive, //����
		Dead,  //���S
		Clear
	};
	State _state;
	enum Kind
	{
		Player,
		Enemy,
		Block,
		SmallEnemy,
		Sumi,
	};
	Kind _kind;
<<<<<<< HEAD
	int _isEnemy; //�G���m�̏Փ˔���̓���Enemy���ʗp
=======
	//int _
>>>>>>> 5a76b1d00273134d99a116fb0b8cc5e9357f4554
};