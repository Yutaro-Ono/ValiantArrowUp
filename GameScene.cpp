#include "GameScene.h"

void Scene::Init()
{
	soundEnter = LoadSoundMem("data/Sound/SE/Menu/MENU_CURSOR_ENTER.mp3");
}

// �V�[���̈ڍs�������s���֐�
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
		// ���S��
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
		// �N���A���AZ�Ń^�C�g���֖߂�
		if (CheckHitKey(KEY_INPUT_Z))
		{
			manager = STATE_INIT;
		}
		// �N���A���AX�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_X))
		{
			manager = STATE_ENDGAME;
		}
		break;
	case STATE_GAMEOVER:
		// �Q�[���I�[�o�[���AZ�Ń^�C�g���֖߂�
		if (CheckHitKey(KEY_INPUT_Z))
		{
			manager = STATE_INIT;
		}
		// �Q�[���I�[�o�[���AX�ŃQ�[���I��
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
