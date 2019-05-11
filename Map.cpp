#include "Map.h"

void Map::Init()
{
	//drawNumX = 1920 / MAP_SIZE + 2;
	//drawNumY = 1080 / MAP_SIZE + 2;

	graph = LoadGraph("data/textures/MapTile/mapchip1.png");

	drawNumX = MAP_WIDTH;
	drawNumY = MAP_HEIGHT;
}

void Map::Create()
{
	int num;
	char str;
	char chip[3];
	FILE* fp;		// ファイルのポインタ
					// Map.csvをfpに読み取り形式で開く
	fopen_s(&fp, "data/Strings/Map.csv", "r");

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			num = 0;
			while ((str = fgetc(fp)) != '\n' && str != ',')
			{
				chip[num++] = str;
			}
			map[i][j] = atoi(chip);
		}
	}
	// ファイルを閉じる
	fclose(fp);
}

void Map::Draw(Camera *camera, Player *player)
{

	// マップを描く(横)
	for (int i = 0; i < drawNumY; i++)
	{
		// マップを描く(縦)
		for (int j = 0; j < drawNumX; j++)
		{
			DrawRectGraph(j * MAP_SIZE - camera->camOffsetX, i * MAP_SIZE - camera->camOffsetY,			// 画面の表示位置 x, y
				map[i][j] * MAP_SIZE, 0,						// 元画像の切り出し位置 x, y
				MAP_SIZE, MAP_SIZE,								// 切り出しサイズ　幅・高さ
				graph, TRUE, false);
		}
	}

}

int Map::GetNumX(float x)
{
	return (int)(x / MAP_SIZE);
}

int Map::GetNumY(float y)
{
	return (int)(y / MAP_SIZE);
}

int Map::GetType(float x, float y)
{
	return map[GetNumY(y)][GetNumX(x)];
}