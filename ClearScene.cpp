#include "ClearScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"

void ClearScene::Initialize()
{
	_clearImage = GraphFactory::Instance().LoadGraph("img\\pipo-battlebg003b.jpg");
}

void ClearScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\pipo-battlebg003b.jpg");
}

void ClearScene::Update()
{
	DrawGraph(0, 0, _clearImage, FALSE);

	//�L�[���͂��X�V
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//�X�y�[�X�L�[����������Q�[���J�n
	if (key & PAD_INPUT_10)
	{
		//�V�[�����Q�[���V�[���ɐ؂�ւ���
		SceneManager::Instance().LoadScene("Title");
	}
}
