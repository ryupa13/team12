#include "TitleScene.h"
#include"DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Sound.h"
#include "Renderer.h"
#include "WindowInfo.h"
#include "TileMap.h"

//������
void TitleScene::Initialize()
{
	//�^�C�g���̔w�i�̉摜�ǂݍ���

	_titleImage = GraphFactory::Instance().LoadGraph("img\\clear.png");

	//�g�摜
	_frameImage = GraphFactory::Instance().LoadGraph("img\\waku.png");
	//SE�ǂݍ���
	_titleSE = Sound::Instance().LoadSE("sound\\se\\sentaku.wav");
	_cursorSE = Sound::Instance().LoadSE("sound\\se\\test.wav");
	//BGM�Đ�
	Sound::Instance().PlayBGM("sound\\bgm\\title2.mp3", DX_PLAYTYPE_LOOP);
	//�J�[�\���ԍ�
	_cursorNumber = 0;
}

//�X�V
void TitleScene::Update()
{
	//�^�C�g����ʂ�\������
	Renderer::Instance().DrawGraph(_titleImage, Vector2());

	//�X�y�[�X�L�[����������Q�[���J�n
	if (Input::GetKeyTrigger(KEY_INPUT_SPACE))
	{
		switch (_cursorNumber)
		{
		case 0: //�X�e�[�W�I��
			SceneManager::Instance().LoadScene("Select");
			break;
		case 1: //�`���[�g���A��
			TileMap::Instance().Start("stage\\Tutorial.csv", 3);
			SceneManager::Instance().LoadScene("Game");
			break;
		}
		Sound::Instance().PlaySE(_titleSE, DX_PLAYTYPE_BACK);
		Sound::Instance().StopBGM();
	}

	//�J�[�\���̈ړ�
	if (Input::GetKeyTrigger(KEY_INPUT_DOWN))
	{
		Sound::Instance().PlaySE(_cursorSE, DX_PLAYTYPE_BACK);
		_cursorNumber += 1;

		if (_cursorNumber > 1)
			_cursorNumber = 1;
	}
	if (Input::GetKeyTrigger(KEY_INPUT_UP))
	{
		Sound::Instance().PlaySE(_cursorSE, DX_PLAYTYPE_BACK);
		_cursorNumber -= 1;

		if (_cursorNumber < 0)
			_cursorNumber = 0;
	}

	//�J�[�\���̕`��
	//Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 + 197, 268 + _cursorNumber * 138));

	Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 - 162, 362 + _cursorNumber * 138));

}

//���
void TitleScene::Release()
{

	GraphFactory::Instance().EraseGraph("img\\clear.png");

	GraphFactory::Instance().EraseGraph("img\\waku.png");
}
