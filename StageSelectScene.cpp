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
	//�l�p�摜
	_squareImage = GraphFactory::Instance().LoadGraph("img\\square.png");
	//�g�摜
	_frameImage = GraphFactory::Instance().LoadGraph("img\\frame.png");

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
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 - 64 * 4, WindowInfo::WindowHeight / 2 - 64));
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 - 64, WindowInfo::WindowHeight / 2 - 64));
	Renderer::Instance().DrawGraph(_squareImage, Vector2(WindowInfo::WindowWidth / 2 + 64 * 2, WindowInfo::WindowHeight / 2 - 64));

	//Z�L�[�������ꂽ��
	if (Input::GetKeyTrigger(KEY_INPUT_Z))
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
	if (Input::GetKeyTrigger(KEY_INPUT_RIGHT))
	{
		_stageNumber += 1;

		if (_stageNumber > _stageNumberLimit)
			_stageNumber = _stageNumberLimit;
	}
	if (Input::GetKeyTrigger(KEY_INPUT_LEFT))
	{
		_stageNumber -= 1;

		if (_stageNumber < 0)
			_stageNumber = 0;
	}

	//�J�[�\���̕`��
	Renderer::Instance().DrawGraph(_frameImage, Vector2(WindowInfo::WindowWidth / 2 - 64 * 4 + 64 * _stageNumber * 3, WindowInfo::WindowHeight / 2 - 64));
}

void StageSelectScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\select.png");
	GraphFactory::Instance().EraseGraph("img\\square.png");
	GraphFactory::Instance().EraseGraph("img\\frame.png");
}