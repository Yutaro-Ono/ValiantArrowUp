#pragma once
#include "Common.h"
class Player;
class Camera;


class Bg
{
public:

	int graph1;
	int graph2;
	int graph3;
	int setumeiGraph;
	float bgX;
	float bgDefaultX;

	int animTimer;
	int frameCount;

	void Init();
	void Update(Camera *camera);
	void DrawFront(Camera *camera, Player *player);
	void DrawBack(Camera *camera, Player *player);
};