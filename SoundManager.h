#pragma once
#include "Common.h"

class Scene;
class Boss;
class Sound
{
public:

	int titleBgm;
	int gameBgm;
	int bossBgm;
	int clearBgm;
	int gameoverBgm;

	void Init();
	void MusicControl(Scene * scene, Boss * boss);

};