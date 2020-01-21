#pragma once
#include <DxLib.h>
#include <string>
#include <unordered_map>

class Sound final
{
private:
	//�C���X�^���X�����𐧌�
	//�R���X�g���N�^
	Sound() {}

	//�R�s�[�R���X�g���N�^
	Sound(const Sound&) {}

	//�R�s�[������Z�q
	Sound& operator= (const Sound&) {}

public:
	//�C���X�^���X�̎擾
	static Sound& Instance();

	//SE�����[�h����
	int LoadSE(std::string filepath);

	//SE���폜����
	void EraseSE(std::string filepath);

	//SE���Đ�����
	void PlaySE(int se, int type);

	//SE���Đ������`�F�b�N
	bool CheckSE(int se);

	//SE���~�߂�
	void StopSE(int se);

	//BGM���Đ�����
	void PlayBGM(std::string filepath, int type);

	//BGM���Đ������`�F�b�N
	bool CheckBGM();

	//BGM���~�߂�
	void StopBGM();

private:
	//�T�E���h�n���h���̃L���b�V��
	std::unordered_map<std::string, int> _soundCache;
};