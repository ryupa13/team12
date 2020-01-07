#pragma once

//シーンの基底クラス
class BaseScene
{
public:
	// () = 0 にすることで純粋仮想関数になった
	//初期化
	virtual void Initialize() = 0;

	//更新
	virtual void Update() = 0;

	//解放
	virtual void Release() = 0;
};