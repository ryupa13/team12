#pragma once
#include "BaseScene.h"
#include <unordered_map>

enum SceneState
{
	Initialize, //初期化
	Update,     //更新
	Release,    //解放
};

//シーン管理クラス
class SceneManager
{
private:
	//シングルトンクラスなのでコンストラクタなどを再生成できなくする
	SceneManager() : _state(SceneState::Initialize),
		_currentScene(nullptr), _nextScene(nullptr) { }
	SceneManager(const SceneManager&) {}
	SceneManager& operator = (const SceneManager&) {}

public:
	//デストラクタ
	~SceneManager();

	//インスタンスを取得
	static SceneManager& Instance();

	//シーンを追加する
	void AddScene(std::string sceneName, BaseScene* basescene);

	//最初のシーンを設定
	void StartScene(std::string sceneName);

	//シーン遷移
	void LoadScene(std::string sceneName);

	//更新処理
	void Update();

private:
	//シーンの更新処理
	void SceneUpdate();

	//次のシーンがあるかどうか？
	void NextScene();

private:
	BaseScene* _currentScene;//現在のシーン
	BaseScene* _nextScene;//次のシーン
	SceneState _state;//シーンの状態
	std::unordered_map<std::string, BaseScene*>_scenes;
};