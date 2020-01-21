#pragma once
#include "Vector2.h"
#include "GameObject.h"
#include"SumiShot.h"
#include<unordered_map>


//	�v���C���[�N���X
//	��GameObject�N���X���p������
class Player : public GameObject
{
public:
	//	�J�n
	//	��override�C���q���g�p���邱�Ƃ�
	//	���̃����o�֐������N���X�ɑ��݂��Ȃ��ꍇ�A�G���[���o�͂���
	void Start() override;

	//	�`��
	void Render()  override;

	//	�X�V
	void Update()  override;

	//�@���
	void Release()  override;

	

	void UpdateMotion();

	//�@�q�b�g�ʒm
	void Hit() override;
	void Hit(GameObject *hitObject) override;
	void Hit(bool hitX, bool hitY) override;

	//�@
	void UpdatePosition(bool hitX, bool hitY);
	enum PDirection
	{
		DOWN, UP, RIGHT, LEFT,
	};
	PDirection pDirection;
private:
	const int AnimationSpeed = 4;
	const int HorizonSheet = 5;
	const int VerticalSheet = 2;

	
public:
	//	�摜�n���h��
	int _grp;
	int count;
	int su;
	SumiShot _sumishot;
	std::unordered_map<PDirection, Vector2>_maps{
		{PDirection::DOWN,Vector2 (0,1)},
	{PDirection::UP,Vector2(0,-1)},
	{PDirection::LEFT,Vector2(-1,0)},
	{PDirection::RIGHT,Vector2(1,0)}
	    
	};
	int anime[8];
	int AnimationCount;
	int ImgIndex;
	int animenum;
};