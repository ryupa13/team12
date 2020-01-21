#include "SumiShot.h"
#include "GameObjectManager.h"
#include"Input.h"

SumiShot::~SumiShot()
{
	for (auto shot : _shotList)
	{
		delete shot;
	}
}

void SumiShot::Shot(const Vector2& pos,const Vector2& velocity )
{
	Sumi*shot = new Sumi(pos,velocity);

	//_shotList.push_back(shot);
	GameObjectManager::Instance().Add(shot);
}

void SumiShot::Shot(const Vector2 & pos, float angle)
{
	GameObject *shot = new Sumi(pos, angle);
	//	_shotList.push_back(shot);

	GameObjectManager::Instance().Add(shot);
}

void SumiShot::Update()
{
	
	//for (auto it = _shotList.begin(); it != _shotList.end();) {
	//	(*it)->Update();

	//	if ((*it)->Position().x > WindowInfo::WindowWidth)
	//	{
	//		delete *it;
	//		it = _shotList.erase(it);
	//		continue;
	//	}
	//	++it;
	//}
}

void SumiShot::Render()
{
	for (auto shot : _shotList) {
		shot->Render();
	}
}
