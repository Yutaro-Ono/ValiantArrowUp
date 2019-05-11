#pragma once
#include "Common.h"

class Effect
{
	public:

	//---------------------------------------------//
	// ショットのヒット時のエフェクト
	//--------------------------------------------//
	//
	int shotHitPosX;
	int shotHitPosY;

	int playerPosX;
	int playerPosY;

	int hitCounter;

	int effTimer;
	int effCounter;

	// 弾が当たると立つフラグ
	bool shotOccurFlg;
	// 弾が当たった時、弾がどの向きで当たったかを判別するためのフラグ
	bool shotHitDir;

	int shotHitEff[6];
	int shotCharge[6];

	void Init();
	// エフェクト発生時の座標を取得する関数
	void Targeting(Player *player, Shot *shot);
	// フェードアウト処理を行う関数
	void FadeOut(Camera *camera, int FileName);
	// ショットがヒットしたときのエフェクト
	void ShotHitDraw(Camera *camera, Anim *anim);
	void ShotCharge1(Camera *camera, Player *player, Anim *anim);
	void ShotCharge2(Camera *camera, Player *player, Anim *anim);
};