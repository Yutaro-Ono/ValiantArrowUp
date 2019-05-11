#pragma once
#include "Common.h"
class Anim;
class Player;
class Legion;
class UI;

class Enemy
{
public:

	float	x;
	float	y;

	// 体力
	int hp;

	// 向き
	bool dir;

	enum State
	{
		STATE_MOVE,
		STATE_ATTACK,
		STATE_DIE,
	};

	// ステートのキー
	int manager;

	// 移動しているかしていないか
	bool moveFlg;

	// 移動方向
	bool moveRight;
	bool moveLeft;
	// 画像情報は"EnemyLegion"で処理

	// 死亡
	bool dieFlg;

	// 落下フラグ
	bool fallFlg;

	// ダメージ関連
	bool hitFlg;		// 矢に当たったかどうか
	bool damageFlg;		// ダメージを受けた時に立つフラグ
	int damageCounter;		// 被ダメージ時カウント
	float damageFlyDist;	// 被ダメージ時リアクションの横方向距離
	float damageVelocity;	// 被ダメージ時リアクションの上方向距離

	// ハーピー用変数
	bool  upDown;
	int	  maxFly;

	// 当たり判定用フラグ
	bool	hitTop;
	bool	hitUnder;
	bool	hitRight;
	bool	hitLeft;


	void	Init();
	void	Update();
	void	MoveRoutine(int i);
	void	DamageReaction(Player *player, int i);
	void	TrackRoutine(Player *player);
	void	Died(UI *ui);
	void	Gravity(int i);
	void	HitBlockVoid(Collision *coll, Map *map);
	void	HitBlockTop(Camera *camera, Collision *coll, Map *map);
	void	HitBlockUnder(Camera *camera, Collision *coll, Map *map);
	void	HitBlockRight(Camera *camera, Collision *coll, Map *map, Player * player);
	void	HitBlockLeft(Camera *camera, Collision *coll, Map *map, Player * player);
	void	Draw(Camera *camera, Anim *anim, UI *ui);
};