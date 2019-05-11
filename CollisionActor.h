#pragma once
#include "Common.h"

class Player;
class Enemy;
class Boss;
class Shot;
class Item;

class CollisionActor
{
public:
	
	float playerTop;
	float playerUnder;
	float playerLeft;
	float playerRight;

	float enemyTop;
	float enemyUnder;
	float enemyLeft;
	float enemyRight;

	float bossTop;
	float bossUnder;
	float bossLeft;
	float bossRight;

	float shotTop;
	float shotUnder;
	float shotLeft;
	float shotRight;

	float laserTop;
	float laserUnder;
	float laserLeft;
	float laserRight;

	float itemTop;
	float itemUnder;
	float itemLeft;
	float itemRight;

	void HitEtoP(Player *player, Enemy *enemy);
	void HitBoss(Player *player, Boss *boss);
	void HitEnemShot(Enemy *enemy, Shot *shot);
	void HitBossShot(Boss * boss, Shot * shot);
	void HitBossLaser(Boss * boss, Player * player);
	void HitItem(Player * player, Item * item);
	void HitShotItem(Shot * shot, Item * item);
};