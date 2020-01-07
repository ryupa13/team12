#pragma once
#include <DxLib.h>
#include "GraphFactory.h"
#include "Vector2.h"

//Rendererクラス
//final指定子　継承禁止
class Renderer final
{
private:
	//外部からのインスタンス生成を制限
	//コンストラクタ
	Renderer() {}

	//コピーコンストラクタ
	Renderer(const Renderer&) {}

	//コピー代入演算子
	Renderer& operator= (const Renderer&) {}

public:
	//インスタンスの取得
	static Renderer& Instance();

	//画像の描画(画像サイズそのまま)
	void DrawGraph(int grp, Vector2 position);

	//画像の描画(拡大縮小)
	void DrawGraph(int grp, Vector2 position, Vector2 bottomRightPosition);

	//画像の描画(回転　拡大無し)
	void DrawGraph(int grp, Vector2 position, Vector2 centerPosition, double angle);

	//画像の描画(回転　拡大有り)
	void DrawGraph(int grp, Vector2 position, Vector2 centerPosition, double extRate, double angle);

	//画像の描画(切り取り)
	void DrawGraph(int grp, Vector2 position, Vector2 graphPosition, Vector2 size);
};