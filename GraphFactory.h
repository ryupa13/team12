#pragma once
#include <DxLib.h>
#include <string>
#include <memory>
#include <unordered_map>

//
//	画像を読み込みキャッシュするクラスの作成
//	※final指定子を使用することで継承禁止のクラスとする
class GraphFactory final
{
private:
	//	シングルトンは外部からのインスタンス生成を制限するので
	//	コンストラクタ
	GraphFactory() {
	}

	//	コピーコンストラクタ
	GraphFactory(const GraphFactory&) {
	}

	//	コピー代入演算子
	GraphFactory& operator= (const GraphFactory&) {
	}
public:

	//	インスタンスの取得
	static GraphFactory& Instance();

	//	グラフィックをロードする
	int LoadGraph(std::string filepath);

	//	グラフィックを削除する
	void EraseGraph(std::string filepath);

	//	デバッグログを表示する
	void ShowDebugLog();

private:
	//	グラフィックハンドルのキャッシュ
	std::unordered_map<std::string, int> _graphCache;
};