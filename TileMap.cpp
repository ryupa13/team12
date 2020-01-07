#include "TileMap.h"
#include <DxLib.h>
#include "GraphFactory.h"
#include<fstream>
#include<sstream>

TileMap& TileMap::Instance()
{
	static std::unique_ptr<TileMap> instance(new TileMap());

	return *instance;
}

//������
void TileMap::Start()
{
	//�摜�̓ǂݍ���
	_mapgrp = GraphFactory::Instance().LoadGraph("img\\maptipsample.png");

#pragma region �z��̃}�b�v
	////�^�C���}�b�v�̏����쐬
//_map = 
//{
//	{11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
//	{11, 0, 0, 0, 0, 0, 0, 0,80,11, 0, 0, 0, 0, 0, 0,11, 0, 0,11},
//	{11, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0,65,66, 0, 0,11, 0, 0,11},
//	{11, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0,75,76, 0, 0,11, 0, 0,11},
//	{11, 0, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0,11, 0, 0,11},
//	{11, 0, 0,11,11, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0,11},
//	{11, 0, 0, 0,11, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0,11},
//	{11, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11},
//	{11, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11},
//	{11, 0, 0, 0,11,11,11,11,11,11, 0, 0,11, 0, 0, 0,44,45, 0,11},
//	{11, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0,54,55, 0,11},
//	{11, 0,70, 0,11, 0, 0,16, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0,11},
//	{11, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0,11},
//	{11, 0, 0, 0,11, 0, 0, 0, 0, 0, 0, 0,11, 0, 0, 0, 0, 0, 0,11},
//	{11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
//};//�z��̃}�b�v
#pragma endregion

	//�}�b�v��ǂݍ���
	std::ifstream ifs("stage\\SampleStage.csv");

	//�t�@�C���̓ǂݍ��݂ɐ���������
	if (ifs)
	{
		//��������P�s���ǂݍ���
		std::string line;
		while (std::getline(ifs, line))
		{
			//�ǂݍ��񂾕�������J���}��؂�ŕ���
			std::vector<int>data = Split(line);

			//�}�b�v�����i�[
			_map.push_back(data);
		}

		int x = 0, y = 0;
		for (auto row : _map)
		{
			x = 0;

			for (auto col : row)
			{
				if (col > 0)
				{

				}
				x++;
			}
			y++;
		}
	}

	//1�^�C���}�b�v�̃T�C�Y��ݒ�
	_tilesize = 64;
}

//	�`��
void TileMap::Render()
{
	//X�̈ʒu��Y�̈ʒu
	int x = 0, y = 0;

	//�}�b�v�����s�P�ʂœǂݍ���
	for (auto row : _map)
	{
		x = 0;

		//�}�b�v�����擾����
		for (auto col : row)
		{
			//���n�̕`��
			DrawRectGraph(x*_tilesize, y*_tilesize, 0, 0,
				_tilesize, _tilesize, _mapgrp, TRUE);

			//�}�b�v�̕`��
			auto destX = col % 10;
			auto destY = (col / 10) % 10;

			DrawRectGraph(x*_tilesize, y*_tilesize, destX*_tilesize, destY*_tilesize,
				_tilesize, _tilesize, _mapgrp, TRUE);

			//X�����Ƀ^�C���}�b�v��1�i�߂�
			x++;
		}
		//Y�����Ƀ^�C���}�b�v��1�i�߂�
		y++;
	}
}

//���݈ʒu+�T�C�Y+�ړ��ʂ��猻�݂̏Փˏ�Ԃ��擾����
TileHitInfo TileMap::FindTileHitInfo(const Vector2 & pos, const Vector2 & size, const Vector2 & velocity)
{
	//������s���L�����̒��S���W���擾
	Vector2 center = Vector2((pos.x) + (size.x / 2), (pos.y) + (size.y / 2));

	//X�����̔���
	auto hitx = TileCollision(center, size, Vector2(velocity.x, 0));

	//Y�����̔���
	auto hity = TileCollision(center, size, Vector2(0, velocity.y));

	//�Փˌ��ʂ��i�[����
	TileHitInfo info =
	{
		false,
		false,
		0
	};

	//AND���Z�q���g�p���A�Փ˂��Ă���ꍇ��1�A
	//���Ă��Ȃ��ꍇ��0�Ƃ���
	info._hitX = (hitx & 1);
	info._hitY = (hity & 1);

	//�Փ˂����I�u�W�F�N�g�̔ԍ����擾����
	info._no = (hitx >> 8) | (hity >> 8);

	return info;
}

//�^�C���}�b�v�̏Փ˔�����s��
int TileMap::TileCollision(const Vector2 & pos, const Vector2 & size, const Vector2 & velocity)
{
	//������u����v�u�E��v�u�����v�u�E���v�ɂȂ�悤�ɔz����i�[
	auto sizeX = static_cast<int>(size.x / 2);
	auto sizeY = static_cast<int>(size.y / 2);
	std::vector<int>imageWidth = { -sizeX,sizeX,-sizeX,sizeX };
	std::vector<int>imageHeight = { -sizeY,-sizeY,sizeY,sizeY };

	for (unsigned int index = 0; index < imageWidth.size(); index++)
	{
		//���S���W+�e�T�C�Y+�ړ��ʂŏՓ˔�����s��
		unsigned int x = static_cast<int>(pos.x + imageWidth[index] + velocity.x) / _tilesize;
		unsigned int y = static_cast<int>(pos.y + imageHeight[index] + velocity.y) / _tilesize;

		//�z��͈̔͊O���Q�Ƃ����牽�����Ȃ�
		if (y >= _map.size())
		{
			continue;
		}
		if (x >= _map[y].size())
		{
			continue;
		}

		//0�o�Ȃ��ꍇ�A��������̃I�u�W�F�N�g�ɏՓ˂���
		if (_map[y][x] > 0)
		{
			//����8�r�b�g�̏Փ˃t���O�A��ʂW�r�b�g�ɏՓ˂����I�u�W�F�N�g����
			return 1 | (_map[y][x] << 8);
		}
	}
	//���������������Ă��Ȃ�
	return 0;
}

std::vector<int> TileMap::Split(const std::string & str, char delim)
{
	//�����񑀍���s�����ߕ�����X�g���[����錾
	std::stringstream iss(str);
	std::string tmp;
	std::vector<int> mapRow;

	//��������J���}��؂�œǂݍ���
	while (std::getline(iss, tmp, delim))
	{
		mapRow.push_back(std::atoi(tmp.c_str()));
	}
	return mapRow;
}
