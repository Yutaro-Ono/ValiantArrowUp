#include "Interface.h"

void UI::Init()
{
	// ���j���[�֘A
	menuLogo			=		LoadGraph("Data/Interface/MenuIcon/MENU_TITLE_LOGO.png", TRUE);
	menuBg				=		LoadGraph("Data/Interface/MenuIcon/MENU_TITLE_BACKGROUND.png", TRUE);
	menuPlay[0]			=		LoadGraph("Data/Interface/MenuIcon/MENU_TITLE_PLAY_1.png", TRUE);
	menuPlay[1]			=		LoadGraph("Data/Interface/MenuIcon/MENU_TITLE_PLAY_2.png", TRUE);
	menuTutorial[0]		=		LoadGraph("Data/Interface/MenuIcon/MENU_TITLE_TUTORIAL_1.png", TRUE);
	menuTutorial[1]		=		LoadGraph("Data/Interface/MenuIcon/MENU_TITLE_TUTORIAL_2.png", TRUE);
	menuQuit[0]			=		LoadGraph("Data/Interface/MenuIcon/MENU_TITLE_QUIT_1.png", TRUE);
	menuQuit[1]			=		LoadGraph("Data/Interface/MenuIcon/MENU_TITLE_QUIT_2.png", TRUE);
	menuBar				=		LoadGraph("Data/Interface/MenuIcon/MENU_TITLE_BAR.png", TRUE);
	menuTutorialWindow	=		LoadGraph("Data/Interface/MenuIcon/MENU_TUTORIAL.png", TRUE);
	menuCursorMove		=		LoadGraph("Data/Interface/MenuIcon/MENU_CURSOR_MOVE.png", TRUE);
	menuEnter			=		LoadGraph("Data/Interface/MenuIcon/MENU_ENTER.png", TRUE);

	// HUD
	char file_name[256];
	// HUD�ǂݍ���
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(file_name, "Data/Interface/HUD/UI_HUD_MAIN_%d.png", i);
		mainHUD[i] = LoadGraph(file_name, TRUE);
	}

	// �̗̓{�b�N�X�ǂݍ���
	for (int i = 0; i < 6; i++)
	{
		sprintf_s(file_name, "Data/Interface/HUD/HP/UI_HP_Block_%d.png", i);
		lifeBox[i] = LoadGraph(file_name, TRUE);
	}
	// �X�^�[�ǂݍ���
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(file_name, "Data/Interface/HUD/Score/UI_Score_Star_%d.png", i);
		scoreStar[i] = LoadGraph(file_name, TRUE);
	}

	resultBack			=		LoadGraph("Data/Interface/MenuIcon/RESULT_WALL.png", TRUE);
	gameClear			=		LoadGraph("Data/Interface/MenuIcon/MENU_GAMECLEAR.png", TRUE);
	gameOver			=		LoadGraph("Data/Interface/MenuIcon/MENU_GAMEOVER.png", TRUE);
	iconRetry			=		LoadGraph("Data/Interface/MenuIcon/Z_CONTINUE.png", TRUE);
	iconQuit			=		LoadGraph("Data/Interface/MenuIcon/X_QUIT.png", TRUE);

	soundCursor = LoadSoundMem("data/Sound/SE/Menu/MENU_CURSOR_CHOICE.mp3");


	menuTutorialX = 360;
	menuTutorialY = 1380;
	menuTutorialFlg = false;

	// ���j���[�o�[�̓_��
	barCount = 0;
	barFadeFlg = false;

	// �X�R�A�֘A
	score = 0;
	scoreX = 0.0f;
	scoreY = 0.0f;

	menuCursor = 0;
	pushButton = false;

	// ��_���[�W
	bloodCount = 0;
	bloodSpray1 = LoadGraph("Data/Textures/Effects/SCRN_BLD_SPARY_1.png", TRUE);
	bloodSpray2 = LoadGraph("Data/Textures/Effects/SCRN_BLD_SPARY_2.png", TRUE);
	bloodScreen1 = LoadGraph("Data/Textures/Effects/SCRN_BLD_1.png", TRUE);
	bloodScreen2 = LoadGraph("Data/Textures/Effects/SCRN_BLD_2.png", TRUE);


	hpBarRed = GetColor(255, 0, 0);
	hpBarGreen = GetColor(0, 255, 255);
}

void UI::LoadFont()
{
	LPCSTR font_path = "Data/Fonts/g_roundbold_kana_004.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	ChangeFont("g_�����t�H���g ����", DX_CHARSET_DEFAULT);
}

// �^�C�g�����j���[UI�̕`��
void UI::titleDraw()
{
	DrawGraph(0, 0, menuBg, TRUE);
	DrawGraph(20, 30, menuLogo, TRUE);

	if (!(menuCursor == 0))
	{
		DrawGraph(1500, 250, menuPlay[0], TRUE);
	}
	if (!(menuCursor == 1))
	{
		DrawGraph(1100, 400, menuTutorial[0], TRUE);
	}
	if (!(menuCursor == 2))
	{
		DrawGraph(1500, 550, menuQuit[0], TRUE);
	}



	DrawRotaGraph(1630, 980, 0.7f, 0, menuCursorMove, TRUE);
	DrawRotaGraph(1735, 850, 0.9f, 0, menuEnter, TRUE);

	// �_�ŏ����p�J�E���^
	if (barFadeFlg == false)
	{
		barCount++;
		if (barCount >= 255)
		{
			barFadeFlg = true;
		}
	}
	if (barFadeFlg == true)
	{
		barCount--;
		if (barCount <= 50)
		{
			barFadeFlg = false;
		}
	}



	if (menuTutorialFlg == true)
	{
		if (menuTutorialY >= 750)
		{
			menuTutorialY -= 10;
		}

		DrawRotaGraph(menuTutorialX, menuTutorialY, 0.8f, 0, menuTutorialWindow, TRUE);
	}

	// �{�^���A�ő΍�
	if (CheckHitKey(KEY_INPUT_UP) == 0 && CheckHitKey(KEY_INPUT_DOWN) == 0 && pushButton == true)
	{
		pushButton = false;
	}

	// �J�[�\���ړ�����(menuBar���d�Ȃ��Ă�ꍇ�A���h��̃A�C�R������ɒu��)
	if (menuCursor == 0)
	{

		SetDrawBlendMode(DX_BLENDMODE_ADD, barCount);
		DrawGraph(1470, 238, menuBar, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawGraph(1500, 250, menuPlay[1], TRUE);

		// �\���L�[�㉺�ŃJ�[�\���ړ�
		if (CheckHitKey(KEY_INPUT_DOWN) == 1 && pushButton == false)
		{
			menuCursor = 1;
			// ���ʉ��Đ�
			PlaySoundMem(soundCursor, DX_PLAYTYPE_BACK);
			pushButton = true;
		}
		if (CheckHitKey(KEY_INPUT_UP) == 1 && pushButton == false)
		{
			menuCursor = 2;
			// ���ʉ��Đ�
			PlaySoundMem(soundCursor, DX_PLAYTYPE_BACK);
			pushButton = true;
		}
	}
	if (menuCursor == 1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, barCount);
		DrawGraph(1070, 388, menuBar, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawGraph(1100, 400, menuTutorial[1], TRUE);

		// �\���L�[�㉺�ŃJ�[�\���ړ�
		if (CheckHitKey(KEY_INPUT_DOWN) == 1 && pushButton == false)
		{
			menuCursor = 2;
			// ���ʉ��Đ�
			PlaySoundMem(soundCursor, DX_PLAYTYPE_BACK);
			pushButton = true;
		}
		if (CheckHitKey(KEY_INPUT_UP) == 1 && pushButton == false)
		{
			menuCursor = 0;
			PlaySoundMem(soundCursor, DX_PLAYTYPE_BACK);
			pushButton = true;
		}
	}
	if (menuCursor == 2)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, barCount);
		DrawGraph(1470, 538, menuBar, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawGraph(1500, 550, menuQuit[1], TRUE);

		// �\���L�[�㉺�ŃJ�[�\���ړ�
		if (CheckHitKey(KEY_INPUT_DOWN) == 1 && pushButton == false)
		{
			menuCursor = 0;
			// ���ʉ��Đ�
			PlaySoundMem(soundCursor, DX_PLAYTYPE_BACK);
			pushButton = true;
		}

		if (CheckHitKey(KEY_INPUT_UP) == 1 && pushButton == false)
		{
			menuCursor = 1;
			// ���ʉ��Đ�
			PlaySoundMem(soundCursor, DX_PLAYTYPE_BACK);
			pushButton = true;
		}
	}
}

void UI::GameClear()
{
	DrawGraph(0, 0, resultBack, TRUE);
	DrawGraph(0, 0, gameClear, TRUE);
	DrawRotaGraph(600, 740, 0.5f, 0, iconRetry, TRUE);
	DrawRotaGraph(1260, 740, 0.5f, 0, iconQuit, TRUE);
}

void UI::GameOver()
{
	DrawGraph(0, 0, resultBack, TRUE);
	DrawGraph(0, 0, gameOver, TRUE);
	DrawRotaGraph(600, 740, 0.5f, 0, iconRetry, TRUE);
	DrawRotaGraph(1260, 740, 0.5f, 0, iconQuit, TRUE);
}

void UI::DrawHUD()
{
	DrawGraph(0, 0, mainHUD[0], TRUE);
}

void UI::DrawHUDframe()
{
	DrawGraph(0, 0, mainHUD[1], TRUE);
}

void UI::DrawLifebox(Player * player)
{
	for (int i = 0; i < player->hp; i++)
	{
		DrawGraph(0, 0, lifeBox[i], TRUE);
	}
}

// �̗̓o�[(�ėp)�\��
void UI::HealthBar(Camera *camera, float x, float y, int w, int h, int hp, int qua_hp)
{
	if(!(qua_hp == hp))
	{
		for (int i = 1; i <= hp; i++)
		{
			DrawBox(camera->GetScreenX(x - w), camera->GetScreenY(y - h - 10), camera->GetScreenX((x - w) + (w * 2 / hp) * (i)), camera->GetScreenY((y - h)), hpBarRed, TRUE);
		}
		for (int i = 1; i <= qua_hp; i++)
		{
			DrawBox(camera->GetScreenX(x - w), camera->GetScreenY(y - h - 10), camera->GetScreenX((x - w) + (w * 2 / hp) * (i)), camera->GetScreenY((y - h)), hpBarGreen, TRUE);
		}
	}
}

void UI::AddScore(int tag)
{
	// �o���[���Ƀq�b�g���X�R�A���Z
	if (tag == 0)
	{
		score += SCORE_BAL_ADD;
	}
	// �G���G�q�b�g���X�R�A���Z
	if (tag == 1)
	{
		score += SCORE_ENEM_ADD;
	}
}

void UI::DrawScore()
{
	// �X�R�A(�����Ƃ̈ʒu�����̂��ߏ�������)
	if (score == 0)
	{
		DrawFormatString(1690, 40, GetColor(100, 100, 0), "0000", score);
	}
	if (score > 0 && score <= 9999)
	{
		DrawFormatString(1690, 40, GetColor(255, 255, 0), "%d", score);
	}
	if (score >= 10000 && score <= 99999)
	{
		DrawFormatString(1635, 40, GetColor(255, 255, 0), "%d", score);
	}
	if (score >= 100000)
	{
		DrawFormatString(1580, 40, GetColor(255, 255, 0), "%d", score);
	}

	// �X�R�A�����l��˔j�����ۂ̃X�^�[�\��
	if (score >= 15000)
	{
		DrawGraph(0, 0, scoreStar[0], TRUE);
	}
	if (score >= 35000)
	{
		DrawGraph(0, 0, scoreStar[1], TRUE);
	}
	if (score >= 50000)
	{
		DrawGraph(0, 0, scoreStar[2], TRUE);
	}
}

// ��_���[�W���̌��򖗕`��ƁA�̗͈��l�ȉ����̃A���[�g�`��
void UI::SprayBlood(Player * player)
{
	if (player->damageFlg)
	{
		if(player->hp % 2)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * 2 - player->damageCount * 2);
			DrawGraph(0, 0, bloodScreen1, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120 * 2 - player->damageCount * 2);
			DrawGraph(0, 0, bloodScreen2, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	// �̗͒ቺ���̉�ʃG�t�F�N�g
	// �̗�3�`2�܂�
	if (player->hp < 4 && player->hp >= 2)
	{
		if (bloodCount * 5 > 255)
		{
			bloodCount = 0;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - bloodCount * 5);
		DrawGraph(0, 0, bloodScreen2, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		bloodCount++;

	}
	// �̗�1�ȉ�
	else if (player->hp < 2)
	{
		if (bloodCount * 10 > 255)
		{
			bloodCount = 0;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - bloodCount * 10);
		DrawGraph(0, 0, bloodScreen1, TRUE);
		DrawGraph(0, 0, bloodScreen2, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		bloodCount++;
	}
}
