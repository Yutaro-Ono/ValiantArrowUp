#pragma once
#include "Common.h"
class Player;
class Map;
class Camera;
class Boss;

class Debug
{
public:

	int flg;

	void Init();
	void Escape();
	void Tyousa(Player *player, Enemy *enemy, Item * item, Boss * boss, Map *map, Camera *camera, Shot *shot, Effect *effect);
};