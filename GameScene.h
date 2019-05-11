#pragma once
#include "Common.h"

class Player;
class Boss;
class UI;


class Scene
{
	public:

	enum State
	{
		STATE_INIT,
		STATE_TITLE,
		STATE_TUTORIAL,
		STATE_INTRO,
		STATE_GAME,
		STATE_CLEAR,
		STATE_GAMEOVER,
		STATE_ENDGAME
	};

	// ÉÅÉjÉÖÅ[âÊñ ëIëâπ
	int soundEnter;

	int manager = STATE_INIT;


	void Init();

	void Control(Player *player, Boss * boss, UI *ui);

	int TitleProcess();

	int TutorialProcess();

	int GameProcess();

	int ClearProcess();

	int GameOverProcess();
};