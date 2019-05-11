#pragma once
#include "Common.h"

class Player;


class UI
{
	public:

	//-----------------------------------------------------//
	// タイトルメニュー関連
	//----------------------------------------------------//
	// メニュー画面アイコン格納
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

	// リザルト画面
	int resultBack;
	int gameClear;
	int gameOver;
	int iconRetry;
	int iconQuit;


	// 操作説明画像の座標とフラグ
	int menuTutorialX;
	int menuTutorialY;
	bool menuTutorialFlg;

	// カーソル処理用
	int menuCursor;
	// ボタンを押したか押していないかのフラグ
	bool pushButton;

	// メニュー画面サウンド関連
	int soundCursor;

	// 選択バーカウンター
	int barCount;
	bool barFadeFlg;

	// スコア関連
	int score;

	float scoreX;
	float scoreY;

	// ダメージ時の血飛沫エフェクト用
	int bloodCount;
	int bloodSpray1;
	int bloodSpray2;
	int bloodScreen1;
	int bloodScreen2;

	// 体力バー用
	int hpBarRed;
	int hpBarGreen;

	int arrowUI;
	int arrowMenu;

    // スコア加算
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