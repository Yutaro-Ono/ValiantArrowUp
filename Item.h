#pragma once
#include "Common.h"
class Player;
class Anim;
class Shot;


class Item
{
public:

	// 座標
	float posX;
	float posY;

	// アイテムの種類
	enum Type
	{
		TYPE_CURE,
		TYPE_SCORE
	};
	// 種類格納用
	int type;


	// 回復アイテム
	int cureItem[5];
	// スコアアイテム
	int scoreItem[5];

    // エフェクト
    int cureEffect[6];
	int cureSound;

	int explSound;

	// 見えているかいないかのフラグ
	bool visibleFlg;

    // 消滅時のエフェクト発生
    bool hitEffect;
    
	// プレーヤーに当たったかどうか
	bool hitFlg;

	// アニメーション用タイマー
	int animTimer;
	int animCounter;

	// 関数
	void InitItem(int i);
	void SetPos(int i);
	void hitPlayer(Player * player);
	void hitArrow(UI * ui);
	void CurePlayer(Player * player);
	void DrawItem(Anim * anim, Camera * camera);
    void DrawEffect(Anim * anim, Camera * camera, Player * player);
};