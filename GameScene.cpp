#include "GameScene.h"
#include <DxLib.h>
#include "GraphFactory.h"
#include "SceneManager.h"
#include "WindowInfo.h"
#include "GameObjectManager.h"
#include "Enemy.h"

void GameScene::Initialize()
{
	//�^�C�g���̔w�i�̉摜�ǂݍ���
	_gameImage = GraphFactory::Instance().LoadGraph("img\\pipo-battlebg001b.jpg");

	_tileMap.Start();
	_player = new Player();
	GameObjectManager::Instance().Start();
	GameObjectManager::Instance().Add(_player);
	GameObjectManager::Instance().Add(new Enemy(Vector2(1000, 200)));
	GameObjectManager::Instance().Add(new Enemy(Vector2(1000, 400)));
}

void GameScene::Update()
{
	//�^�C�g����ʂ�\������
	//DrawGraph(0, 0, _gameImage, FALSE);

	GameObjectManager::Instance().Update();

	_tileMap.Render();
	GameObjectManager::Instance().Render();

	auto info = _tileMap.FindTileHitInfo((*_player).Position(), (*_player).Size(), (*_player).Velocity());
	GameObjectManager::Instance().TileMapCollision(info._hitX, info._hitY);

	if (info._hitX == 1 || info._hitY == 1)
	{
		if (info._no == 80)
		{
			SceneManager::Instance().LoadScene("Clear");
		}
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
	GraphFactory::Instance().EraseGraph("img\\pipo-battlebg001b.jpg");
}
