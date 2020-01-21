#pragma once
#include <DxLib.h>
#include "GraphFactory.h"
#include "Vector2.h"

//Renderer�N���X
//final�w��q�@�p���֎~
class Renderer final
{
private:
	//�O������̃C���X�^���X�����𐧌�
	//�R���X�g���N�^
	Renderer() {}

	//�R�s�[�R���X�g���N�^
	Renderer(const Renderer&) {}

	//�R�s�[������Z�q
	Renderer& operator= (const Renderer&) {}

public:
	//�C���X�^���X�̎擾
	static Renderer& Instance();

	//�摜�̕`��(�摜�T�C�Y���̂܂�)
	void DrawGraph(int grp, Vector2 position);

	//�摜�̕`��(�g��k��)
	void DrawGraph(int grp, Vector2 position, Vector2 bottomRightPosition);

	//�摜�̕`��(��]�@�g�喳��)
	void DrawGraph(int grp, Vector2 position, Vector2 centerPosition, double angle);

	//�摜�̕`��(��]�@�g��L��)
	void DrawGraph(int grp, Vector2 position, Vector2 centerPosition, double extRate, double angle);

	//�摜�̕`��(�؂���)
	void DrawGraph(int grp, Vector2 position, Vector2 graphPosition, Vector2 size);
};