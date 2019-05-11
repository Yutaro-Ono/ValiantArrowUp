#pragma once
#include "Common.h"

class Anim;
class Camera;
class Map;
class Collision;
class Player;

class Boss
{
	public:

	int graph[6];
	int standGraph;

	// ボスの状態を格納
	int state;

	// 座標
	float x;
	float y;
	// 体力
	int hp;
	// 方向フラグ
	bool dir;
	// 動いているかいないかのフラグ
	bool moveFlg;
	// 前に移動するか後ろに移動するかのフラグ(STATE_MOVE時に使用)
	bool moveDirection;
	bool changeDirection;
	// 死亡フラグ
	bool dieFlg;
	// 移動からターゲット状態に移るまでのカウント
	int moveCount;

	// ボスのボディにヒット
	bool hitBody;
	int hitCount;
	// ボスの弱点にヒット
	bool hitWeak;

	// ターゲット状態(上:ターゲット状態に入った時の現在時刻を格納、下:)
	int targetTimer;
	int targetCount;
	bool targetFlg;

	// ターゲット時の足元エフェクト関連
	float tagEffX;
	float tagEffY;

	// レーザー発射関連
	bool flashFlg;
	bool laserFlg;
	int flashCounter;
	int laserTimer;
	int laserCount;

	// エフェクト関連
	int shieldEffect[10];
	int tagEff[6];
	int tagChargeEff[8];
	int laserFlash[6];
	int laserGraph[6];

	// 効果音
	int chargeSound;
	int flashSound;
	int laserSound;
	int footstepSound;
	int shieldSound;

	// アニメーション用カウンター
	int animCounter;



	enum State
	{
		STATE_FREEZE,
		STATE_MOVE,
		STATE_TARGET,
		STATE_ATTACK,
		STATE_RAGE,
		STATE_DEATH
	};



	void Init();
	void Routine(Player * player);
	void HitShotBody();
	void Damage();
	void Draw(Anim * anim, Camera * camera);
	void DrawEffect(Anim * anim, Camera * camera);
};