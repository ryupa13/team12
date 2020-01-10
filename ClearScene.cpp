#include "ClearScene.h"
#include "DxLib.h"
#include "GraphFactory.h"
#include "SceneManager.h"
#include "Input.h"

void ClearScene::Initialize()
{
	_clearImage = GraphFactory::Instance().LoadGraph("img\\clear.png");
}

void ClearScene::Release()
{
	GraphFactory::Instance().EraseGraph("img\\clear.png");
}

void ClearScene::Update()
{
	DrawGraph(0, 0, _clearImage, FALSE);

	//�X�y�[�X�L�[����������Q�[���J�n
	if (Input::GetKeyTrigger(KEY_INPUT_SPACE))
	{
		//�V�[�����Q�[���V�[���ɐ؂�ւ���
		SceneManager::Instance().LoadScene("Title");
	}
}
