#include "Sound.h"
#include <memory>

//�C���X�^���X���擾����
Sound & Sound::Instance()
{
	static std::unique_ptr<Sound> instance(new Sound());

	return *instance;
}

//SE�����[�h����
//���Ƀ��[�h�ς݂̏ꍇ�L���b�V�����g�p����
int Sound::LoadSE(std::string filepath)
{
	//�T�E���h�n���h�����L���b�V������Ă��Ȃ����SE��ǂݍ���
	if (!_soundCache.count(filepath))
	{
		//SE�����[�h���T�E���h�n���h�����L���b�V������
		auto se = DxLib::LoadSoundMem(filepath.c_str());

		//�L���b�V���̓t�@�C���p�X���L�[�Ƃ���
		_soundCache[filepath] = se;
	}

	return _soundCache[filepath];
}

//SE���폜����
//�L���b�V������Ă��Ȃ��ꍇ�͉������Ȃ�
void Sound::EraseSE(std::string filepath)
{
	//�T�E���h�n���h�����L���b�V������Ă��Ȃ���Ή������Ȃ�
	if (!_soundCache.count(filepath))
		return;

	//�T�E���h�n���h���̃L���b�V�����擾
	auto se = _soundCache[filepath];

	//�T�E���h�n���h�����폜
	DxLib::DeleteSoundMem(se);

	//�L���b�V�����폜
	_soundCache.erase(filepath);
}

void Sound::PlaySE(int se, int type)
{
	DxLib::PlaySoundMem(se, type);
}

bool Sound::CheckSE(int se)
{
	if (DxLib::CheckSoundMem(se) == 1)
		return true; //�Đ���
	return false; //�Đ����Ă��Ȃ�
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
		return true; //�Đ���
	return false; //�Đ����Ă��Ȃ�
}

void Sound::StopBGM()
{
	DxLib::StopMusic();
}