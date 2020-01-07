#pragma once
#include <DxLib.h>
#include <string>
#include <memory>
#include <unordered_map>

//
//	�摜��ǂݍ��݃L���b�V������N���X�̍쐬
//	��final�w��q���g�p���邱�ƂŌp���֎~�̃N���X�Ƃ���
class GraphFactory final
{
private:
	//	�V���O���g���͊O������̃C���X�^���X�����𐧌�����̂�
	//	�R���X�g���N�^
	GraphFactory() {
	}

	//	�R�s�[�R���X�g���N�^
	GraphFactory(const GraphFactory&) {
	}

	//	�R�s�[������Z�q
	GraphFactory& operator= (const GraphFactory&) {
	}
public:

	//	�C���X�^���X�̎擾
	static GraphFactory& Instance();

	//	�O���t�B�b�N�����[�h����
	int LoadGraph(std::string filepath);

	//	�O���t�B�b�N���폜����
	void EraseGraph(std::string filepath);

	//	�f�o�b�O���O��\������
	void ShowDebugLog();

private:
	//	�O���t�B�b�N�n���h���̃L���b�V��
	std::unordered_map<std::string, int> _graphCache;
};