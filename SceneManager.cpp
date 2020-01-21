#include "SceneManager.h"
#include <memory>
#include "DxLib.h"
#include "Input.h"

//デストラクタ
SceneManager::~SceneManager()
{
	for (auto scene : _scenes)
	{
		delete scene.second;
	}
}

//クラスのインスタンスを取得
SceneManager & SceneManager::Instance()
{
	static std::unique_ptr<SceneManager> instance(new SceneManager);

	return *instance;
}

//シーンを追加
void SceneManager::AddScene(std::string sceneName, BaseScene * basescene)
{
	if (_scenes.count(sceneName)) return;

	_scenes[sceneName] = basescene;
}

//最初のシーンを設定
void SceneManager::StartScene(std::string sceneName)
{
	if (!_scenes.count(sceneName)) return;
	_currentScene = _scenes[sceneName];
}

//次のシーンへ
void SceneManager::LoadScene(std::string sceneName)
{
	if (!_scenes.count(sceneName)) return;

	_nextScene = _scenes[sceneName];
	_state = SceneState::Release;
}

void SceneManager::Update()
{
	//メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//背景をクリアする
		ClearDrawScreen();

		//Input更新
		Input::Update();

		//シーンを更新する
		SceneUpdate();

		//反転
		ScreenFlip();
	}
}

//シーンの更新処理
void SceneManager::SceneUpdate()
{
	if (!_currentScene) return;

	//初期化
	if (_state == SceneState::Initialize)
	{
		_currentScene->Initialize();
		_state = SceneState::Update;
	}

	//更新処理
	_currentScene->Update();

	//解放処理
	if (_state == SceneState::Release)
	{
		_currentScene->Release();
		NextScene();
		_state = SceneState::Initialize;
	}
}

//次のシーンに切り替える
void SceneManager::NextScene()
{
	_currentScene = _nextScene;
}

