#pragma once
#include <list>
#include "GameObject.h"
#include "Collision.h"
#include "Player.h"

class GameObjectManager
{
private:
	GameObjectManager() {}
	GameObjectManager(const GameObjectManager&) {}
	GameObjectManager& operator = (const GameObjectManager&) {}

public:
	//�f�X�g���N�^
	~GameObjectManager();

	//�C���X�^���X���擾
	static GameObjectManager& Instance();

	//�J�n
	void Start();

	//�X�V
	void Update();

	//�`��
	void Render();

	//GameObject��ǉ�����
	void Add(GameObject* gameObject);

	//�^�C���}�b�v�̏Փ˔���
	void TileMapCollision();

	Vector2 GetPlayerPosition();
	Vector2 GetPlayerSize();
	Vector2 GetPlayerVelocity();
	bool GetClearFlag();
	Vector2 SearchSumis(Vector2 pos, float rad);

private:
	//�v���C���[�ƃG�l�~�[�̓����蔻��
	void HitToCharacters();

	//�u���b�N�Ƃ̓����蔻��
	void HitToBlocks();

	//�n�̓����蔻��
	void HitToSumis();

	//�G�l�~�[���m�̓����蔻��
	void HitToEnemys();

	//���S�I�u�W�F�N�g�̍폜
	void RemoveDeadGameObjects();

private:
	std::list<GameObject*> _players; //�v���C���[���X�g
	std::list<GameObject*> _enemys;  //�G�l�~�[���X�g
	std::list<GameObject*> _blocks;  //�u���b�N���X�g
	std::list<GameObject*> _addNewGameObjects; //�ǉ�����Q�[���I�u�W�F�N�g���X�g
	std::list<GameObject*> _sumis; //�n���X�g

	Collision _collision;
};