#include "StageSelectScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Renderer.h"
#include "WindowInfo.h"
#include "TileMap.h"
#include"Sound.h"

void StageSelectScene::Initialize()
{
	//�I����ʂ̔w�i�̉摜�ǂݍ���
	_selectImage = GraphFactory::Instance().LoadGraph("img\\select.png");
	//�g�摜
	_frameImage = GraphFactory::Instance().LoadGraph("img\\selectplayer.png");
	//BGM�Đ�
	Sound::Instance().PlayBGM("sound\\bgm\\title2.mp3", DX_PLAYTYPE_LOOP);

	_gamesceneSE = Sound::Instance().LoadSE("sound\\se\\sentaku.wav");
	_gameEXsceneSE = Sound::Instance().LoadSE("sound\\se\\yaro.wav");
	_crr = Sound::Instance().LoadSE("sound\\se\\test.wav");

	//�J�[�\�������킹�Ă���X�e�[�W�ԍ�
	_stageNumber = 0;
	//�X�e�[�W�ԍ��̏��
	_stageNumberLimit = 2;
}

void StageSelectScene::Update()
{
	//�w�i��\������
	Renderer::Instance().DrawGraph(_selectImage, Vector2(0, 0));
	//�X�e�[�W�ꗗ��\������
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 - 64, WindowInfo::WindowHeight / 2 - 64));
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 + 64 * 2, WindowInfo::WindowHeight / 2 - 64));

	
	//SPACE�L�[�������ꂽ��
	if (Input::GetKeyTrigger(KEY_INPUT_SPACE))
	{
		//�J�[�\�������킹�Ă����X�e�[�W�ԍ��ɉ����ă}�b�v��ǂݍ���
		switch (_stageNumber)
		{
		case 0:
			TileMap::Instance().Start("stage\\stage01.csv", 0);
			break;
		case 1:
			TileMap::Instance().Start("stage\\stage02.csv", 1);
			break;
		case 2:
			TileMap::Instance().Start("stage\\stage03.csv", 2);
			break;
		case 3:
			TileMap::Instance().Start("stage\\stage04.csv", 4);
			break;
		default:
			break;
		}

		//�V�[�����Q�[���V�[���ɐ؂�ւ���
		SceneManager::Instance().LoadScene("Game");
		Sound::Instance().PlaySE(_gamesceneSE, DX_PLAYTYPE_BACK);
		Sound::Instance().StopBGM();
	}

	if (Input::GetKeyTrigger(KEY_INPUT_H))
	{
		Sound::Instance().PlaySE(_gameEXsceneSE, DX_PLAYTYPE_BACK);
		_stageNumber = 3;
	}

	if (Input::GetKeyTrigger(KEY_INPUT_DOWN))
	{
		Sound::Instance().PlaySE(_crr, DX_PLAYTYPE_BACK);
		_stageNumber += 1;

		if (_stageNumber > _stageNumberLimit)
			_stageNumber = _stageNumberLimit;
	}
	if (Input::GetKeyTrigger(KEY_INPUT_UP))
	{
		Sound::Instance().PlaySE(_crr, DX_PLAYTYPE_BACK);
		_stageNumber -= 1;

		if (_stageNumber < 0)
			_stageNumber = 0;
	}

	//�J�[�\���̕`��

	Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 - 128, WindowInfo::WindowHeight / 2 - 150 + _stageNumber * 150));

}

void StageSelectScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\select.png");

	GraphFactory::Instance().EraseGraph("img\\selectplayer.png");
}