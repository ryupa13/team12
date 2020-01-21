#include "ClearScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Renderer.h"
#include "WindowInfo.h"

void ClearScene::Initialize()
{
	//�w�i�摜
	_clearImage = GraphFactory::Instance().LoadGraph("img\\title.png");
	//�g�摜
	_frameImage = GraphFactory::Instance().LoadGraph("img\\waku.png");

	//�J�[�\���ԍ�
	_cursorNumber = 0;
}

void ClearScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\clear.png");
	GraphFactory::Instance().EraseGraph("img\\waku.png");
}

void ClearScene::Update()
{
	//�w�i��\������
	Renderer::Instance().DrawGraph(_clearImage, Vector2());

	//SPACE�L�[�������ꂽ��
	if (Input::GetKeyTrigger(KEY_INPUT_SPACE))
	{
		switch (_cursorNumber)
		{
		case 0: //�^�C�g��
			SceneManager::Instance().LoadScene("Title");
			break;
		case 1: //�X�e�[�W�I��
			SceneManager::Instance().LoadScene("Select");
			break;
		default:
			break;
		}
	}

	//�J�[�\���̈ړ�
	if (Input::GetKeyTrigger(KEY_INPUT_RIGHT))
	{
		_cursorNumber += 1;

		if (_cursorNumber > 1)
			_cursorNumber = 1;
	}
	if (Input::GetKeyTrigger(KEY_INPUT_LEFT))
	{
		_cursorNumber -= 1;

		if (_cursorNumber < 0)
			_cursorNumber = 0;
	}

	//�J�[�\���̕`��
	Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 - 559 + _cursorNumber * 787, WindowInfo::WindowHeight / 2 - 62));
}
