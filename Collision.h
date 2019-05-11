#pragma once
#include "Common.h"
class Camera;
class Map;
class Player;
class Enemy;
class Shot;

//------------------------------------------------------------------------------//
// 当たり判定クラス(ブロック関連)
//-----------------------------------------------------------------------------//
class Collision
{
public:

	bool CheckHitTop(Map *map, float x, float y, int sizeW, int sizeH);
	bool CheckHitUnder(Map *map, float x, float y, int sizeW, int sizeH);
	bool CheckHitRight(Map *map, float x, float y, int sizeW, int sizeH);
	bool CheckHitLeft(Map *map, float x, float y,int sizeW, int sizeH);

};