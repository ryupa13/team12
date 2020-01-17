#pragma once
#include "GameObject.h"
#include "Player.h"

//�G�l�~�[�N���X
class SmallEnemy : public GameObject
{
public:
	//�R���X�g���N�^
	SmallEnemy() {}
	SmallEnemy(int isEnemy, Vector2 position) { _isEnemy = isEnemy, _position = position; }

	//�J�n
	void Start() override;

	//�`��
	void Render() override;

	//�X�V
	void Update() override;

	//�q�b�g�ʒm
	void Hit() override;
	void Hit(GameObject *hitObject);
	void Hit(bool hitX, bool hitY) override;

	//���
	void Release() override;

private:
	void UpdateVelocity();
	void UpdatePosition(bool hitX, bool hitY);

public:
	//�摜�n���h��
	int _grp;
	//�v���C���[���W
	Vector2 _playerPosition;
	//�v���C���[���m�͈�
	float _searchPlayerRadius;
	//�n���m�͈�
	float _searchInkRadius;
	//���m���
	enum SearchState
	{
		Chase,
		Free,
		Ink
	};
	SearchState _search;
	int _stateCount;
	int _chaseCount;
	bool _hitWallX;
	bool _hitWallY;
	int _rnd;
	float _speed;
	Vector2 _length;
};