#include "GameScene.h"
#include <DxLib.h>
#include "GraphFactory.h"
#include "SceneManager.h"
#include "WindowInfo.h"
#include "GameObjectManager.h"
#include "Enemy.h"
#include "SmallEnemy.h"
#include "TileMap.h"

void GameScene::Initialize()
{
	TileMap::Instance().Start();

	GameObjectManager::Instance().Start();
	GameObjectManager::Instance().Add(new Player());
	GameObjectManager::Instance().Add(new Enemy(Vector2(64 * 5, 64 * 5)));
	GameObjectManager::Instance().Add(new Enemy(Vector2(64 * 9, 64 * 9)));
	GameObjectManager::Instance().Add(new SmallEnemy(Vector2(64 * 11, 64)));
}

void GameScene::Update()
{
	//�^�C�g����ʂ�\������
	//DrawGraph(0, 0, _gameImage, FALSE);

	//�X�V
	GameObjectManager::Instance().Update();

	//�`��
	TileMap::Instance().Render();
	GameObjectManager::Instance().Render();

	//�^�C���}�b�v�Ƃ̓����蔻��
	GameObjectManager::Instance().TileMapCollision();

	if (GameObjectManager::Instance().GetClearFlag())
	{
		SceneManager::Instance().LoadScene("Clear");
	}

	//�L�[���͂��X�V
	//int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	////�X�y�[�X�L�[����������Q�[���J�n
	//if (key & PAD_INPUT_10)
	//{
	//	//�V�[�����Q�[���V�[���ɐ؂�ւ���
	//	SceneManager::Instance().LoadScene("Clear");
	//}
}

void GameScene::Release()
{

}
