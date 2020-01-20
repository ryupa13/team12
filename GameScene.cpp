#include "GameScene.h"
#include <DxLib.h>
#include "GraphFactory.h"
#include "SceneManager.h"
#include "WindowInfo.h"
#include "GameObjectManager.h"
#include "Enemy.h"
#include "SmallEnemy.h"
#include "TileMap.h"
#include"Renderer.h"

void GameScene::Initialize()
{
	_gameImage = GraphFactory::Instance().LoadGraph("img\\pipo-charachip005.png");
	GameObjectManager::Instance().Start();
	GameObjectManager::Instance().Add(new Player());
	GameObjectManager::Instance().Add(new Enemy(0, Vector2(64 * 5, 64 * 4)));
	GameObjectManager::Instance().Add(new Enemy(1, Vector2(64 * 9, 64 * 9)));
	GameObjectManager::Instance().Add(new SmallEnemy(2, Vector2(64 * 11, 64)));
}

void GameScene::Update()
{
	//�X�V
	GameObjectManager::Instance().Update();

	//�`��
	TileMap::Instance().Render();
	GameObjectManager::Instance().Render();
	
	for (int i = 1; i < GameObjectManager::Instance().GetBulletCnt() + 1; i++)
	{
		Renderer::Instance().DrawGraph(_gameImage, Vector2(WindowInfo::WindowWidth - i * 64, 0), Vector2(0, 0), Vector2(64, 64));
	}

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
