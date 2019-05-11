#pragma once
#include "Common.h"

class Enemy;

class Legion
{
	public:

	const int enemyNum = 15;

	// エネミーの画像を取得する関数
	void GetImage(const char* imgFileName, const char* fileNameHarpy);

	// エネミーにPositionをセットする関数
	void SetPos(Enemy *enemy, int i);

	// エネミーの描画
	void Draw(Enemy * enemy, Anim * anim, Camera * camera, int i);
};