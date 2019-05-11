#include "Collision.h"

// ブロックの上部当たり判定処理
bool Collision::CheckHitTop(Map *map, float x, float y, int sizeW, int sizeH)
{
	// GetTypeで現在プレイヤーがいる座標のブロック添え字を割り出し、0以外で
	if (map->GetType(x + sizeW, y + sizeH) != 0 ||
		map->GetType(x - sizeW, y + sizeH) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// ブロックの底部当たり判定処理
bool Collision::CheckHitUnder(Map *map, float x, float y, int sizeW, int sizeH)
{
	if (map->GetType(x + sizeW, y - sizeH) != 0 ||
		map->GetType(x - sizeW, y - sizeH) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// ブロック右側の当たり判定処理
bool Collision::CheckHitRight(Map *map, float x, float y, int sizeW, int sizeH)
{
	if (map->GetType(x - sizeW, y + sizeH / 2) != 0 ||
		map->GetType(x - sizeW, y - sizeH / 2) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// ブロック左側の当たり判定処理
bool Collision::CheckHitLeft(Map *map, float x, float y, int sizeW, int sizeH)
{
	if (map->GetType(x + sizeW, y + sizeH / 2) != 0 ||
		map->GetType(x + sizeW, y - sizeH / 2) != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}