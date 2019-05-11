#include "Common.h"

// 敵に共通で使用するグローバル変数
int enemyMoff[6];
int enemyHarpy[6];

// エネミーの画像を取得する
void Legion::GetImage(const char* fileNameMoff, const char* fileNameHarpy)
{
	LoadDivGraph(fileNameMoff, 6, 6, 1, ENEMY_W * 2, ENEMY_H * 2, enemyMoff, TRUE);

	LoadDivGraph(fileNameHarpy, 6, 6, 1, ENEMY_W * 2, ENEMY_H * 2, enemyHarpy, TRUE);
}

// エネミーにPositionをセットする
void Legion::SetPos(Enemy * enemy, int i)
{
	if (i == 0)
	{
		enemy->x = 1600;
		enemy->y = 890;
	}
	if (i == 1)
	{
		enemy->x = 2432;
		enemy->y = 640;
	}
	if (i == 2)
	{
		enemy->x = 2496;
		enemy->y = 890;
	}
	if (i == 3)
	{
		enemy->x = 4224;
		enemy->y = 640;
	}
	if (i == 4)
	{
		enemy->x = 3136;
		enemy->y = 640;
	}
	if (i == 5)
	{
		enemy->x = -64;
		enemy->y = 400;
	}
	if (i == 6)
	{
		enemy->x = 3712;
		enemy->y = 890;

	}
	if (i == 7)
	{
		enemy->x = 5888;
		enemy->y = 640;
	}
	if (i == 8)
	{
		enemy->x = 4608;
		enemy->y = 890;
	}
	if (i == 9)
	{
		enemy->x = 6400;
		enemy->y = 512;
	}
	if (i == 10)
	{
		enemy->x = 12864;
		enemy->y = 320;
	}
	if (i == 11)
	{
		enemy->x = 8200;
		enemy->y = 400;
	}
	if (i == 12)
	{
		enemy->x = 8000;
		enemy->y = 890;
	}
	if (i == 13)
	{
		enemy->x = 10752;
		enemy->y = 500;
	}
	if (i == 14)
	{
		enemy->x = 8200;
		enemy->y = 890;
	}
	if (i == 15)
	{
		enemy->x = 11392;
		enemy->y = 500;
	}
	if (i == 16)
	{
		enemy->x = 8732;
		enemy->y = 890;
	}
	if (i == 17)
	{
		enemy->x = 12032;
		enemy->y = 384;
	}
	if (i == 18)
	{
		enemy->x = 9100;
		enemy->y = 890;
	}
	if (i == 19)
	{
		enemy->x = -64;
		enemy->y = 500;
	}
	if (i == 20)
	{
		enemy->x = 9500;
		enemy->y = 890;
	}
	if (i == 21)
	{
		enemy->x = -64;
		enemy->y = 500;
	}
	if (i == 22)
	{
		enemy->x = 11904;
		enemy->y = 890;
	}
	if (i == 23)
	{
		enemy->x = -64;
		enemy->y = 500;
	}

}

void Legion::Draw(Enemy * enemy, Anim * anim, Camera * camera, int i)
{
	// 非死亡時
	if((i % 2) == 0 && !enemy->dieFlg && (enemy->damageFlg == false || enemy->damageFlg == true && enemy->damageCounter % 25 / 8))
	{
		DrawRotaGraph(camera->GetScreenX(enemy->x), camera->GetScreenY(enemy->y), 1.5f, 0, enemyMoff[anim->counter], TRUE, enemy->dir);
	}

	if((i % 2) == 1 && !enemy->dieFlg && (enemy->damageFlg == false || enemy->damageFlg == true && enemy->damageCounter % 25 / 8))
	{
		DrawRotaGraph(camera->GetScreenX(enemy->x), camera->GetScreenY(enemy->y), 1.0f, 0, enemyHarpy[anim->counter], TRUE, enemy->dir);
	}

	// 被ダメージ時描画処理
	if (enemy->damageFlg)
	{
		
	}
}

