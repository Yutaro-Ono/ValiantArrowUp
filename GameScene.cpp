#include "GameScene.h"

void Scene::Init()
{
	soundEnter = LoadSoundMem("data/Sound/SE/Menu/MENU_CURSOR_ENTER.mp3");
}

// シーンの移行処理を行う関数
void Scene::Control(Player *player, Boss * boss, UI *ui)
{
	switch (manager)
	{
	case STATE_INIT:
		break;
	case STATE_TITLE:
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			if (ui->menuCursor == 0)
			{
				PlaySoundMem(soundEnter, DX_PLAYTYPE_BACK);
				manager = STATE_GAME;
			}
			if (ui->menuCursor == 1)
			{
				PlaySoundMem(soundEnter, DX_PLAYTYPE_BACK);
				ui->menuTutorialFlg = true;
			}
			if (ui->menuCursor == 2)
			{
				PlaySoundMem(soundEnter, DX_PLAYTYPE_BACK);
				manager = STATE_ENDGAME;
			}
		}
		break;
	case STATE_TUTORIAL:
		break;
	case STATE_INTRO:
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			manager = STATE_GAME;
		}
		break;
	case STATE_GAME:
		// 死亡時
		if (player->hp <= 0)
		{
			manager = STATE_GAMEOVER;
		}
		if (boss->dieFlg)
		{
			manager = STATE_CLEAR;
		}
		break;
	case STATE_CLEAR:
		// クリア時、Zでタイトルへ戻る
		if (CheckHitKey(KEY_INPUT_Z))
		{
			manager = STATE_INIT;
		}
		// クリア時、Xでゲーム終了
		if (CheckHitKey(KEY_INPUT_X))
		{
			manager = STATE_ENDGAME;
		}
		break;
	case STATE_GAMEOVER:
		// ゲームオーバー時、Zでタイトルへ戻る
		if (CheckHitKey(KEY_INPUT_Z))
		{
			manager = STATE_INIT;
		}
		// ゲームオーバー時、Xでゲーム終了
		if (CheckHitKey(KEY_INPUT_X))
		{
			manager = STATE_ENDGAME;
		}
		break;
	case STATE_ENDGAME:
		break;
	}
}

int Scene::TitleProcess()
{
	return 0;
}

int Scene::TutorialProcess()
{
	return 0;
}

int Scene::GameProcess()
{
	return 0;
}

int Scene::ClearProcess()
{
	return 0;
}

int Scene::GameOverProcess()
{
	return 0;
}
