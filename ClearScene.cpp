#include "ClearScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Renderer.h"
#include "WindowInfo.h"
#include"Sound.h"

void ClearScene::Initialize()
{
	//�w�i�摜
	_clearImage = GraphFactory::Instance().LoadGraph("img\\title.png");
	
	//�g�摜
	_frameImage = GraphFactory::Instance().LoadGraph("img\\waku.png");
	//BGM�Đ�
	Sound::Instance().PlayBGM("sound\\bgm\\clear2.mp3", DX_PLAYTYPE_LOOP);
	clearSE = Sound::Instance().LoadSE("sound\\se\\sentaku.wav");
	_crrl = Sound::Instance().LoadSE("sound\\se\\test.wav");
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
		Sound::Instance().PlaySE(clearSE, DX_PLAYTYPE_BACK);
		Sound::Instance().StopBGM();
	}

	//�J�[�\���̈ړ�
	if (Input::GetKeyTrigger(KEY_INPUT_RIGHT))
	{
		Sound::Instance().PlaySE(_crrl, DX_PLAYTYPE_BACK);
		_cursorNumber += 1;

		if (_cursorNumber > 1)
			_cursorNumber = 1;
	}

	if (Input::GetKeyTrigger(KEY_INPUT_LEFT))
	{
		Sound::Instance().PlaySE(_crrl, DX_PLAYTYPE_BACK);
		_cursorNumber -= 1;

		if (_cursorNumber < 0)
			_cursorNumber = 0;
	}

	//�J�[�\���̕`��
	
	Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 - 559 + _cursorNumber * 787, WindowInfo::WindowHeight / 2 - 62));

}
