#pragma once
#include "Common.h"

class Player;


class UI
{
	public:

	//-----------------------------------------------------//
	// �^�C�g�����j���[�֘A
	//----------------------------------------------------//
	// ���j���[��ʃA�C�R���i�[
	int menuLogo;
	int menuBg;
	int menuPlay[2];
	int menuTutorial[2];
	int menuQuit[2];
	int menuBar;
	int menuTutorialWindow;
	int menuCursorMove;
	int menuEnter;

	// HUD
	int mainHUD[2];
	int lifeBox[6];
	int scoreStar[3];

	// ���U���g���
	int resultBack;
	int gameClear;
	int gameOver;
	int iconRetry;
	int iconQuit;


	// ��������摜�̍��W�ƃt���O
	int menuTutorialX;
	int menuTutorialY;
	bool menuTutorialFlg;

	// �J�[�\�������p
	int menuCursor;
	// �{�^�����������������Ă��Ȃ����̃t���O
	bool pushButton;

	// ���j���[��ʃT�E���h�֘A
	int soundCursor;

	// �I���o�[�J�E���^�[
	int barCount;
	bool barFadeFlg;

	// �X�R�A�֘A
	int score;

	float scoreX;
	float scoreY;

	// �_���[�W���̌��򖗃G�t�F�N�g�p
	int bloodCount;
	int bloodSpray1;
	int bloodSpray2;
	int bloodScreen1;
	int bloodScreen2;

	// �̗̓o�[�p
	int hpBarRed;
	int hpBarGreen;

	int arrowUI;
	int arrowMenu;

    // �X�R�A���Z
    #define SCORE_BAL_ADD 1500
	#define SCORE_ENEM_ADD 1000
	#define SCORE_BOSS_ADD 2000

	void Init();
	void LoadFont();
	void titleDraw();
	void GameClear();
	void GameOver();
	void DrawHUD();
	void DrawHUDframe();
	void DrawLifebox(Player * player);
	void HealthBar(Camera *camera, float x, float y, int w, int h, int hp, int qua_hp);
	void AddScore(int tag);
	void DrawScore();
	void SprayBlood(Player *player);
};