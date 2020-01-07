#include "TitleScene.h"
#include"DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"

//������
void TitleScene::Initialize()
{
	//�^�C�g���̔w�i�̉摜�ǂݍ���
	_titleImage = GraphFactory::Instance().LoadGraph("img\\pipo-battlebg018b.jpg");
}

//�X�V
void TitleScene::Update()
{
	//�^�C�g����ʂ�\������
	DrawGraph(0, 0, _titleImage, FALSE);

	//�L�[���͂��X�V
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//�X�y�[�X�L�[����������Q�[���J�n
	if (key & PAD_INPUT_10)
	{
		//�V�[�����Q�[���V�[���ɐ؂�ւ���
		SceneManager::Instance().LoadScene("Game");
	}
}

//���
void TitleScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\pipo-battlebg018b.jpg");
}
