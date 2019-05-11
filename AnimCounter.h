#pragma once
#include "Common.h"
// アニメーション用のタイマーを司る
class Anim
{
public:

	int timer;
	int counter;

	// アイテムアニメーション用
	int itemCounter;
    int itemBaCounter;

	void InitCount();
	void TimeCounter();
	void ItemCounter();
};