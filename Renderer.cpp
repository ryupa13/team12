#include "Renderer.h"

Renderer& Renderer::Instance()
{
	static std::unique_ptr<Renderer> instance(new Renderer());

	return *instance;
}

void Renderer::DrawGraph(int grp, Vector2 position)
{
	DxLib::DrawGraph(static_cast<int>(position.x),
		static_cast<int>(position.y), grp, TRUE);
}

void Renderer::DrawGraph(int grp, Vector2 position, Vector2 bottomRightPosition)
{
	DxLib::DrawExtendGraph(static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(bottomRightPosition.x),
		static_cast<int>(bottomRightPosition.y), grp, TRUE);
}

void Renderer::DrawGraph(int grp, Vector2 position, Vector2 centerPosition, double angle)
{
	DxLib::DrawRotaGraph2(static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(centerPosition.x),
		static_cast<int>(centerPosition.y), 1, angle, grp, TRUE);
}

void Renderer::DrawGraph(int grp, Vector2 position, Vector2 centerPosition, double extRate, double angle)
{
	DxLib::DrawRotaGraph2(static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(centerPosition.x),
		static_cast<int>(centerPosition.y), extRate, angle, grp, TRUE);
}

void Renderer::DrawGraph(int grp, Vector2 position, Vector2 graphPosition, Vector2 size)
{
	DxLib::DrawRectGraph(static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(graphPosition.x),
		static_cast<int>(graphPosition.y),
		size.x, size.y, grp, TRUE);
}