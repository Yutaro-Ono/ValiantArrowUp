#pragma once
#include "Common.h"
class Camera;
class Map
{
public:

	// マップ定数
	#define MAP_SIZE 64
	#define MAP_WIDTH 300
	#define MAP_HEIGHT 17

	int graph;

	int map[MAP_HEIGHT][MAP_WIDTH];

	float drawPointX;			// 描画するマップのx座標
	float drawPointY;			// 描画するマップのy座標

	float drawNumX;			// 描画するマップチップの数(横)
	float drawNumY;			// 描画するマップチップの数(縦)

	void Init();
	void Create();
	void Draw(Camera *camera, Player *player);
	int GetNumX(float x);
	int GetNumY(float y);
	int GetType(float x, float y);
};

