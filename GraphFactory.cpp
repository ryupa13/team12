#include "GraphFactory.h"

//	�C���X�^���X���擾����
GraphFactory& GraphFactory::Instance()
{
	static std::unique_ptr<GraphFactory> instance(new GraphFactory());

	return *instance;
}

//	�摜�����[�h����
//	���Ƀ��[�h�ς݂̏ꍇ�L���b�V�����g�p����
int GraphFactory::LoadGraph(std::string filepath)
{
	//	�O���t�B�b�N�n���h�����L���b�V������Ă��Ȃ���Ή摜��ǂݍ���
	if (!_graphCache.count(filepath)) {

		//	�摜�����[�h���O���t�B�b�N�n���h�����L���b�V������
		auto grp = DxLib::LoadGraph(filepath.c_str());

		//	�L���b�V���̓t�@�C���p�X���L�[�Ƃ���
		_graphCache[filepath] = grp;
	}

	return _graphCache[filepath];
}

//	�摜���폜����
//	�L���b�V������Ă��Ȃ��ꍇ�������Ȃ�
void GraphFactory::EraseGraph(std::string filepath)
{
	//	�O���t�B�b�N�n���h�����L���b�V������Ă��Ȃ���΂Ȃɂ����Ȃ�
	if (!_graphCache.count(filepath))
		return;

	//	�O���t�B�b�N�n���h���̃L���b�V�����擾
	auto grp = _graphCache[filepath];

	//	�O���t�B�b�N�n���h�����폜
	DxLib::DeleteGraph(grp);

	//	�L���b�V�����폜
	_graphCache.erase(filepath);
}

//	�f�o�b�O���O��\������
void GraphFactory::ShowDebugLog()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�摜�̃L���b�V���� : %d", _graphCache.size());
}

