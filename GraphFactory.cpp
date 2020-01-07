#include "GraphFactory.h"

//	インスタンスを取得する
GraphFactory& GraphFactory::Instance()
{
	static std::unique_ptr<GraphFactory> instance(new GraphFactory());

	return *instance;
}

//	画像をロードする
//	既にロード済みの場合キャッシュを使用する
int GraphFactory::LoadGraph(std::string filepath)
{
	//	グラフィックハンドルがキャッシュされていなければ画像を読み込む
	if (!_graphCache.count(filepath)) {

		//	画像をロードしグラフィックハンドルをキャッシュする
		auto grp = DxLib::LoadGraph(filepath.c_str());

		//	キャッシュはファイルパスをキーとする
		_graphCache[filepath] = grp;
	}

	return _graphCache[filepath];
}

//	画像を削除する
//	キャッシュされていない場合何もしない
void GraphFactory::EraseGraph(std::string filepath)
{
	//	グラフィックハンドルがキャッシュされていなければなにもしない
	if (!_graphCache.count(filepath))
		return;

	//	グラフィックハンドルのキャッシュを取得
	auto grp = _graphCache[filepath];

	//	グラフィックハンドルを削除
	DxLib::DeleteGraph(grp);

	//	キャッシュを削除
	_graphCache.erase(filepath);
}

//	デバッグログを表示する
void GraphFactory::ShowDebugLog()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "画像のキャッシュ数 : %d", _graphCache.size());
}

