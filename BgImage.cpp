#include "BgImage.h"

void Bg::Init()
{
	bgX = 0;
	bgDefaultX = 0;

	animTimer = 0;
	frameCount = 0;
	graph1 = LoadGraph("data/background_forest_1.png");
	graph2 = LoadGraph("data/background_forest_2.png");
	graph3 = LoadGraph("data/forestBg2.png");
	setumeiGraph=LoadGraph("data/setumei.png");
}

void Bg::Update(Camera *camera)
{
	bgX = camera->camOffsetX;
}

void Bg::DrawFront(Camera *camera, Player *player)
{

	DrawGraph(bgDefaultX - bgX * 1.1f, 0, graph1, true);
	
	//if (bgX > 0)
	//{
		//DrawGraph(SCREEN_W - bgX, 0, graph1, true);
	//}

	// 説明
	//DrawGraph(0, 0, setumeiGraph, true);
	
}

void Bg::DrawBack(Camera *camera, Player *player)
{
	DrawGraph(0, 0, graph3, true);

	DrawGraph(bgDefaultX - bgX / 8, 0, graph2, true);
	
	//if (bgX > 0)
	//{
		//DrawGraph(SCREEN_W - bgX, 0, graph2, true);
	//}

}