#include "GameScene.h"
#include <DxLib.h>
#include "GraphFactory.h"
#include "SceneManager.h"
#include "WindowInfo.h"

void GameScene::Initialize()
{
	//�^�C�g���̔w�i�̉摜�ǂݍ���
	_gameImage = GraphFactory::Instance().LoadGraph("img\\pipo-battlebg001b.jpg");

	_tileMap.Start();
	_player.Start();
	HitX = false;
	HitY = false;
}

void GameScene::Update()
{
	//�^�C�g����ʂ�\������
	//DrawGraph(0, 0, _gameImage, FALSE);

	_player.Update();
	auto info = _tileMap.FindTileHitInfo(_player.Position(), _player.Size(), _player.Velocity());
	_player.UpdatePosition(info._hitX, info._hitY);

	_tileMap.Render();
	_player.Render();

	if (info._hitX == 1 || info._hitY == 1)
	{
		if (info._no == 80)
		{
			//�V�[�����Q�[���V�[���ɐ؂�ւ���
			SceneManager::Instance().LoadScene("Clear");
		}
	}

	if (info._hitX == 1)
	{
		HitX = true;
	}
	else HitX = false;

	if (info._hitY == 1)
	{
		HitY = true;
	}
	else HitY = false;

#ifdef _DEBUG_
	DrawFormatString(20, 50, GetColor(255, 255, 255), "HitX : %d HitY : %d No : %d ", info._hitX, info._hitY, info._no);
#endif	


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
