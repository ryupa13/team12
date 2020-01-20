#include "GameOverScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Renderer.h"
#include "WindowInfo.h"

void GameOverScene::Initialize()
{
	//�w�i�摜
	_gameoverImage = GraphFactory::Instance().LoadGraph("img\\fould.png");
	//�l�p�摜
	_squareImage = GraphFactory::Instance().LoadGraph("img\\square2.png");
	//�g�摜
	_frameImage = GraphFactory::Instance().LoadGraph("img\\frame2.png");

	//�J�[�\���ԍ�
	_cursorNumber = 0;
}

void GameOverScene::Update()
{
	//�w�i��\������
	Renderer::Instance().DrawGraph(_gameoverImage, Vector2());
	//�I������\������
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 - 450, 194));
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 - 450, 364));
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 - 450, 534));

	//Z�L�[�������ꂽ��
	if (Input::GetKeyTrigger(KEY_INPUT_Z))
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
	Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 - 450, 194 + _cursorNumber * 170));
}

void GameOverScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\fould.png");
	GraphFactory::Instance().EraseGraph("img\\square2.png");
	GraphFactory::Instance().EraseGraph("img\\frame2.png");
}
