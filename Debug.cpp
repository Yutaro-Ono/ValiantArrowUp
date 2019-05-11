#include "Debug.h"

void Debug::Init()
{
	flg = 1;
}

void Debug::Escape()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		flg = 0;
	}
}

void Debug::Tyousa(Player *player, Enemy *enemy, Item * item, Boss * boss,  Map *map, Camera *camera, Shot *shot, Effect *effect)
{
	////
	//if (1)
	//{
	//	printfDx(" %d |", item->hitEffect);
	//}
	//if (CheckHitKey(KEY_INPUT_W))
	//{
	//	player->x = 14000.0f;
	//}
	//if (CheckHitKey(KEY_INPUT_S))
	//{
	//	boss->dieFlg = true;
	//}

 //   CheckJoypadXInput(XINPUT_BUTTON_X);
 //   CheckJoypadXInput(XINPUT_BUTTON_Y);
 //   CheckJoypadXInput(XINPUT_BUTTON_A);
 //   CheckJoypadXInput(XINPUT_BUTTON_B);
}