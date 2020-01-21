#include "GameOverScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Renderer.h"
#include "WindowInfo.h"

void GameOverScene::Initialize()
{
	
	_gameoverImage = GraphFactory::Instance().LoadGraph("img\\overkari.png");
	//�g�摜
	_frameImage = GraphFactory::Instance().LoadGraph("img\\waku.png");

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
		case 1: //�^�C�g��
			SceneManager::Instance().LoadScene("Title");
			break;
		case 2: //�X�e�[�W�I��
			SceneManager::Instance().LoadScene("Select"); 
			break;
		default:
			break;
		}
	}

	//�J�[�\���̈ړ�
	if (Input::GetKeyTrigger(KEY_INPUT_DOWN))
	{
		_cursorNumber += 1;

		if (_cursorNumber > 2)
			_cursorNumber = 2;
	}
	if (Input::GetKeyTrigger(KEY_INPUT_UP))
	{
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
