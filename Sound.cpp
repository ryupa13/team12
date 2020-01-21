#include "Sound.h"
#include <memory>

//インスタンスを取得する
Sound & Sound::Instance()
{
	static std::unique_ptr<Sound> instance(new Sound());

	return *instance;
}

//SEをロードする
//既にロード済みの場合キャッシュを使用する
int Sound::LoadSE(std::string filepath)
{
	//サウンドハンドルがキャッシュされていなければSEを読み込む
	if (!_soundCache.count(filepath))
	{
		//SEをロードしサウンドハンドルをキャッシュする
		auto se = DxLib::LoadSoundMem(filepath.c_str());

		//キャッシュはファイルパスをキーとする
		_soundCache[filepath] = se;
	}

	return _soundCache[filepath];
}

//SEを削除する
//キャッシュされていない場合は何もしない
void Sound::EraseSE(std::string filepath)
{
	//サウンドハンドルがキャッシュされていなければ何もしない
	if (!_soundCache.count(filepath))
		return;

	//サウンドハンドルのキャッシュを取得
	auto se = _soundCache[filepath];

	//サウンドハンドルを削除
	DxLib::DeleteSoundMem(se);

	//キャッシュを削除
	_soundCache.erase(filepath);
}

void Sound::PlaySE(int se, int type)
{
	DxLib::PlaySoundMem(se, type);
}

bool Sound::CheckSE(int se)
{
	if (DxLib::CheckSoundMem(se) == 1)
		return true; //再生中
	return false; //再生していない
}

void Sound::StopSE(int se)
{
	DxLib::StopSoundMem(se);
}

void Sound::PlayBGM(std::string filepath, int type)
{
	DxLib::PlayMusic(filepath.c_str(), type);
}

bool Sound::CheckBGM()
{
	if (DxLib::CheckMusic() == 1)
		return true; //再生中
	return false; //再生していない
}

void Sound::StopBGM()
{
	DxLib::StopMusic();
}