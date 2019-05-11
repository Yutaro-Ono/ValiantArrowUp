#pragma once
#include "Common.h"
class Effect;

class Shot
{
public:
	// 弾の座標
	float x;
	float y;
	// プレーヤーに位置を合わせるためのターゲティング変数
	float adjustX;
	float adjustY;
	// 弾のサイズ
	int w;
	int h;

	// 加速度
	float velocityX;
	float velocityY;

	float speedMultipl;

	float arc;

	int count;

	// 敵にヒットした時のフラグ
	bool	hitFlg;

	// 矢が持つダメージの値
	int damage;
	// 矢のチャージ倍率
	int chargeMag;


	// 残弾数、消去フラグ
	int remain;
	bool visibleFlg;
	bool shotFlg;

	// 放物線用フラグ
	bool downFlg;

	// 弾の向き
	bool dir;

	// エフェクト
	int hitEffect[6];
	bool hitEffectFlg;
	int hitCounter;
	float effectX;
	float effectY;

	// サウンド
	int hitSound;


	// 発射モード
	int mode;

	int graph;

	void Init(Player *player);
	void Update(Player *player);
	void FlyUpdate(Player *player);
    void EraseOut(Camera * camera, Player * player);
	void HitEnemy(Camera *camera, Anim *anim, Enemy *enemy, Effect *effect);
	void HitBlock(Map *map, Collision *coll, Player *player);
	void Draw(Camera *camera, Player *player);
	void DrawHitEffect(Camera * camera);
};