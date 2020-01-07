#include "Collision.h"
#include <math.h>

//	‰~‘Î‰~‚Ì”»’è
bool Collision::CircleCollision(const GameObject* objectA, const GameObject* objectB)
{
	if (objectA == nullptr || objectB == nullptr)
		return false;
	auto x = abs((objectA->Position().x + objectA->Radius()) - (objectB->Position().x + objectB->Radius()));
	auto y = abs((objectA->Position().y + objectA->Radius()) - (objectB->Position().y + objectB->Radius()));

	return (sqrt(x * x + y * y) <= objectA->Radius() + objectB->Radius());
}

//	‹éŒ`‘Î‹éŒ`‚Ì”»’è
bool Collision::RectCollision(const GameObject* objectA, const GameObject* objectB)
{
	if (objectA == nullptr || objectB == nullptr)
		return false;
	auto dx = abs((objectA->Position().x + objectA->Size().x / 2) - (objectB->Position().x + objectB->Size().x / 2));
	auto dy = abs((objectA->Position().y + objectA->Size().y / 2) - (objectB->Position().y + objectB->Size().y / 2));

	return (dx < (objectA->Size().x + objectA->Size().x) / 2 && dy < (objectA->Size().y + objectB->Size().y) / 2);
}
