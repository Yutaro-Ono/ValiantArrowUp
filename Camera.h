#pragma once
#include "Common.h"
class Player;

class Camera
{
public:


	// カメラのオフセット
	float camOffsetX;
	float camOffsetY;


	float tagOffsetX;
	float tagOffsetY;

	void Init();
	void MovePosCam(Player *player);
	
	int  GetScreenX(float tempX);

	int  GetScreenY(float tempY);
};