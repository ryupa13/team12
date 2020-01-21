#include "TitleScene.h"
#include"DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"
#include "Sound.h"

//������
void TitleScene::Initialize()
{
	//�^�C�g���̔w�i�̉摜�ǂݍ���
	_titleImage = GraphFactory::Instance().LoadGraph("img\\title.png");
	//SE�ǂݍ��݃e�X�g
	_titleSE = Sound::Instance().LoadSE("sound\\se\\test.wav");
	//BGM�Đ��e�X�g
	Sound::Instance().PlayBGM("sound\\bgm\\test.mp3", DX_PLAYTYPE_LOOP);
}

//�X�V
void TitleScene::Update()
{
	//�^�C�g����ʂ�\������
	DrawGraph(0, 0, _titleImage, FALSE);

	//�X�y�[�X�L�[����������Q�[���J�n
	if (Input::GetKeyTrigger(KEY_INPUT_SPACE))
	{
		//�V�[�����X�e�[�W�I���V�[���ɐ؂�ւ���
		SceneManager::Instance().LoadScene("Select");
		Sound::Instance().PlaySE(_titleSE, DX_PLAYTYPE_BACK);
		Sound::Instance().StopBGM();
	}
}

//���
void TitleScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\title.png");
}
