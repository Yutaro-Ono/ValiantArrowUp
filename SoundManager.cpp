#include "SoundManager.h"

void Sound::Init()
{
	titleBgm = LoadSoundMem("data/Sound/BGM/TITLE_BGM.mp3");
	gameBgm = LoadSoundMem("data/Sound/BGM/GAME_BGM.mp3");
	bossBgm = LoadSoundMem("data/Sound/BGM/BOSS_BGM.mp3");
	clearBgm = LoadSoundMem("data/Sound/BGM/CLEAR_BGM.mp3");
	gameoverBgm = LoadSoundMem("data/Sound/BGM/GAMEOVER_BGM.mp3");
}

void Sound::MusicControl(Scene * scene, Boss * boss)
{
	if (scene->manager == scene->STATE_TITLE)
	{
		if (CheckSoundMem(clearBgm))
		{
			StopSoundMem(clearBgm);
		}
		if (CheckSoundMem(gameoverBgm))
		{
			StopSoundMem(gameoverBgm);
		}

		if (!CheckSoundMem(titleBgm))
		{
			PlaySoundMem(titleBgm, DX_PLAYTYPE_LOOP);
		}

	}

	if (scene->manager == scene->STATE_GAME && boss->state == boss->STATE_FREEZE)
	{
		if (CheckSoundMem(titleBgm))
		{
			StopSoundMem(titleBgm);
		}
		if (CheckSoundMem(bossBgm))
		{
			StopSoundMem(bossBgm);
		}


		if (!CheckSoundMem(gameBgm))
		{
			PlaySoundMem(gameBgm, DX_PLAYTYPE_LOOP);
		}

	}

	if (scene->manager == scene->STATE_GAME && !(boss->state == boss->STATE_FREEZE))
	{
		if (CheckSoundMem(gameBgm))
		{
			StopSoundMem(gameBgm);
		}
		if (!CheckSoundMem(bossBgm))
		{
			PlaySoundMem(bossBgm, DX_PLAYTYPE_LOOP);
		}


	}

	if (scene->manager == scene->STATE_CLEAR)
	{
		if (CheckSoundMem(gameBgm))
		{
			StopSoundMem(gameBgm);
		}
		if (CheckSoundMem(bossBgm))
		{
			StopSoundMem(bossBgm);
		}
		if (!CheckSoundMem(clearBgm))
		{
			PlaySoundMem(clearBgm, DX_PLAYTYPE_LOOP);
		}



	}

	if (scene->manager == scene->STATE_GAMEOVER)
	{
		if (CheckSoundMem(gameBgm))
		{
			StopSoundMem(gameBgm);
		}
		if (CheckSoundMem(bossBgm))
		{
			StopSoundMem(bossBgm);
		}
		if (!CheckSoundMem(gameoverBgm))
		{
			PlaySoundMem(gameoverBgm, DX_PLAYTYPE_LOOP);
		}



	}
}
