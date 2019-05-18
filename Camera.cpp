#include "Camera.h"

void Camera::Init()
{
	camOffsetX = 0.0f;
	camOffsetY = 0.0f;
	tagOffsetX = 0.0f;
	tagOffsetY = 0.0f;
}

void Camera::MovePosCam(Player *player)
{
	// プレーヤーが画面中心より右もしくは左に移動したときにオフセットも移動する
	if (player->x + PLAYER_W > SCREEN_W / 2 + camOffsetX && player->x > 960.0f)
	{
		tagOffsetX = player->x + PLAYER_SPEED - (SCREEN_W / 2);
	}

	if (player->y + PLAYER_W > SCREEN_H / 2 + camOffsetY && player->y < 540 && player->y > 400)
	{
		tagOffsetY = player->y + GRAVITY_ALL - (SCREEN_H / 2);
	}

	camOffsetX = tagOffsetX;
	camOffsetY = tagOffsetY;
}

// プレーヤーの位置をカメラの中心に据える
int Camera::GetScreenX(float tempX)
{
	// 座標をプレーヤーが進んだ(or戻った)分を記録したオフセットで減じる
	return (int)(tempX - camOffsetX);
}

int Camera::GetScreenY(float tempY)
{
	// 座標をプレーヤーが進んだ(or戻った)分を記録したオフセットで減じる
	return (int)(tempY - camOffsetY);
}