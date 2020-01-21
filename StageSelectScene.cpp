#include "StageSelectScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Renderer.h"
#include "WindowInfo.h"
#include "TileMap.h"

void StageSelectScene::Initialize()
{
	//�I����ʂ̔w�i�̉摜�ǂݍ���
	_selectImage = GraphFactory::Instance().LoadGraph("img\\select.png");
	//�g�摜
	_frameImage = GraphFactory::Instance().LoadGraph("img\\selectplayer.png");

	//�J�[�\�������킹�Ă���X�e�[�W�ԍ�
	_stageNumber = 0;
	//�X�e�[�W�ԍ��̏��
	_stageNumberLimit = 2;
}

void StageSelectScene::Update()
{
	//�w�i��\������
	Renderer::Instance().DrawGraph(_selectImage, Vector2(0, 0));

	//SPACE�L�[�������ꂽ��
	if (Input::GetKeyTrigger(KEY_INPUT_SPACE))
	{
		//�J�[�\�������킹�Ă����X�e�[�W�ԍ��ɉ����ă}�b�v��ǂݍ���
		switch (_stageNumber)
		{
		case 0:
			TileMap::Instance().Start("stage\\stage01.csv");
			break;
		case 1:
			TileMap::Instance().Start("stage\\stage02.csv");
			break;
		case 2:
			TileMap::Instance().Start("stage\\stage03.csv");
			break;
		default:
			break;
		}

		//�V�[�����Q�[���V�[���ɐ؂�ւ���
		SceneManager::Instance().LoadScene("Game");
	}

	//�J�[�\���ړ��A�X�e�[�W�ԍ��̏㉺
	if (Input::GetKeyTrigger(KEY_INPUT_DOWN))
	{
		_stageNumber += 1;

		if (_stageNumber > _stageNumberLimit)
			_stageNumber = _stageNumberLimit;
	}
	if (Input::GetKeyTrigger(KEY_INPUT_UP))
	{
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