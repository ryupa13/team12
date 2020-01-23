#include "DxLib.h"
#include <string>
#include "WindowInfo.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "ClearScene.h"
#include "StageSelectScene.h"
#include "GameOverScene.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//	Windowモードの設定とWindowタイトルを設定する
	ChangeWindowMode(true);
	SetMainWindowText("おいこみ魚");

	//	画面サイズを設定
	SetGraphMode(WindowInfo::WindowWidth, WindowInfo::WindowHeight, 16);
	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	//	描画先を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//	画面背景の色を設定する
	SetBackgroundColor(0, 0, 0);

	//シーンを追加する
	SceneManager::Instance().AddScene("Title", new TitleScene);
	SceneManager::Instance().AddScene("Select", new StageSelectScene);
	SceneManager::Instance().AddScene("Game", new GameScene);
	SceneManager::Instance().AddScene("Clear", new ClearScene);
	SceneManager::Instance().AddScene("Gameover", new GameOverScene);

	//最初のシーンを登録
	SceneManager::Instance().StartScene("Title");

	//実行
	SceneManager::Instance().Update();

	//	解放処理
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}
