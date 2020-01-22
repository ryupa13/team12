#include "GameOverScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Renderer.h"
#include "WindowInfo.h"
#include"Sound.h"

void GameOverScene::Initialize()
{
	
	_gameoverImage = GraphFactory::Instance().LoadGraph("img\\overkari.png");
	//�g�摜
	_frameImage = GraphFactory::Instance().LoadGraph("img\\waku.png");
	//BGM�Đ�
	Sound::Instance().PlayBGM("sound\\bgm\\gameover.mp3", DX_PLAYTYPE_LOOP);
	_gameoverSE = Sound::Instance().LoadSE("sound\\se\\sentaku.wav");
	_cl = Sound::Instance().LoadSE("sound\\se\\test.wav");
	//�J�[�\���ԍ�
	_cursorNumber = 0;
}

void GameOverScene::Update()
{
	//�w�i��\������
	Renderer::Instance().DrawGraph(_gameoverImage, Vector2());
	
	
	//SPACE�L�[�������ꂽ��
	if (Input::GetKeyTrigger(KEY_INPUT_SPACE))
	{
		switch (_cursorNumber)
		{
		case 0: //���g���C
			SceneManager::Instance().LoadScene("Game");
			break;
		case 1: //�X�e�[�W�I��
			SceneManager::Instance().LoadScene("Select");
			break;
		case 2: //�^�C�g��
			SceneManager::Instance().LoadScene("Title"); 
			break;
		}
		Sound::Instance().PlaySE(_gameoverSE, DX_PLAYTYPE_BACK);
		Sound::Instance().StopBGM();
	}

	//�J�[�\���̈ړ�
	if (Input::GetKeyTrigger(KEY_INPUT_DOWN))
	{
		_cursorNumber += 1;
		Sound::Instance().PlaySE(_cl, DX_PLAYTYPE_BACK);
		if (_cursorNumber > 2)
			_cursorNumber = 2;
	}
	if (Input::GetKeyTrigger(KEY_INPUT_UP))
	{
		Sound::Instance().PlaySE(_cl, DX_PLAYTYPE_BACK);
		_cursorNumber -= 1;

		if (_cursorNumber < 0)
			_cursorNumber = 0;
	}

	//�J�[�\���̕`��

	//Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 - 450, 194 + _cursorNumber * 170));

	Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 + 197, 268 + _cursorNumber * 138));

}

void GameOverScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\overkari.png");
	GraphFactory::Instance().EraseGraph("img\\waku.png");
}
