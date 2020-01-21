#pragma once
#include <DxLib.h>
#include <string>
#include <unordered_map>

class Sound final
{
private:
	//インスタンス生成を制限
	//コンストラクタ
	Sound() {}

	//コピーコンストラクタ
	Sound(const Sound&) {}

	//コピー代入演算子
	Sound& operator= (const Sound&) {}

public:
	//インスタンスの取得
	static Sound& Instance();

	//SEをロードする
	int LoadSE(std::string filepath);

	//SEを削除する
	void EraseSE(std::string filepath);

	//SEを再生する
	void PlaySE(int se, int type);

	//SEが再生中かチェック
	bool CheckSE(int se);

	//SEを止める
	void StopSE(int se);

	//BGMを再生する
	void PlayBGM(std::string filepath, int type);

	//BGMが再生中かチェック
	bool CheckBGM();

	//BGMを止める
	void StopBGM();

private:
	//サウンドハンドルのキャッシュ
	std::unordered_map<std::string, int> _soundCache;
};