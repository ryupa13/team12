#include "TitleScene.h"
#include"DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"

//������
void TitleScene::Initialize()
{
	//�^�C�g���̔w�i�̉摜�ǂݍ���
	_titleImage = GraphFactory::Instance().LoadGraph("img\\title.png");
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
	}
}

//���
void TitleScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\title.png");
}
