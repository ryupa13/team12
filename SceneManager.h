#pragma once
#include "BaseScene.h"
#include <unordered_map>

enum SceneState
{
	Initialize, //������
	Update,     //�X�V
	Release,    //���
};

//�V�[���Ǘ��N���X
class SceneManager
{
private:
	//�V���O���g���N���X�Ȃ̂ŃR���X�g���N�^�Ȃǂ��Đ����ł��Ȃ�����
	SceneManager() : _state(SceneState::Initialize),
		_currentScene(nullptr), _nextScene(nullptr) { }
	SceneManager(const SceneManager&) {}
	SceneManager& operator = (const SceneManager&) {}

public:
	//�f�X�g���N�^
	~SceneManager();

	//�C���X�^���X���擾
	static SceneManager& Instance();

	//�V�[����ǉ�����
	void AddScene(std::string sceneName, BaseScene* basescene);

	//�ŏ��̃V�[����ݒ�
	void StartScene(std::string sceneName);

	//�V�[���J��
	void LoadScene(std::string sceneName);

	//�X�V����
	void Update();

private:
	//�V�[���̍X�V����
	void SceneUpdate();

	//���̃V�[�������邩�ǂ����H
	void NextScene();

private:
	BaseScene* _currentScene;//���݂̃V�[��
	BaseScene* _nextScene;//���̃V�[��
	SceneState _state;//�V�[���̏��
	std::unordered_map<std::string, BaseScene*>_scenes;
};