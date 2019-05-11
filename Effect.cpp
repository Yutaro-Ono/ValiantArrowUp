#include "Effect.h"

void Effect::Init()
{
	// 弾のターゲティング用
	shotHitPosX = 0;
	shotHitPosY = 0;
	// プレーヤーのターゲティング用
	playerPosX = 0;
	playerPosY = 0;

	hitCounter = 0;

	effTimer = 0;
	effCounter = 0;

	shotOccurFlg = false;
	shotHitDir = 0;

	LoadDivGraph("Data/textures/Effects/Enemy_Hit/EFFECT_SHOT_HIT.png", 6, 5, 2, 192, 192, shotHitEff, TRUE);
	LoadDivGraph("Data/textures/Effects/Shot/EFFECT_SHOT_CHARGE_2.png", 6, 5, 2, 192, 192, shotCharge, TRUE);
}

void Effect::Targeting(Player *player, Shot *shot)
{
	// ショットが可視化(つまり発射された時点から、弾の座標を取得)
	if (!shot->visibleFlg)
	{
		effTimer = 0;
		effCounter = 0;
		shotHitDir = shot->dir;

		shotHitPosX = shot->x;
		shotHitPosY = shot->y;
	}
	else 
	{
		playerPosX = player->x;
		playerPosY = player->y;
	}

}

void Effect::FadeOut(Camera * camera, int FileName)
{
	
}

void Effect::ShotHitDraw(Camera *camera, Anim *anim)
{
	//// エフェクトの合図が出たらカウント開始し、一定時間後エフェクトを消す
	//if (shotOccurFlg && hitCounter <= 10)
	//{

	//	hitCounter++;

	//	// エフェクトの描画メイン
	//	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	//	if (shotHitDir)
	//	{
	//		DrawRotaGraph(camera->GetScreenX(shotHitPosX) - SHOT_W, camera->GetScreenY(shotHitPosY), 1.5f, 0, shotHitEff[hitCounter / 2], TRUE, 0);
	//	}
	//	if (!shotHitDir)
	//	{
	//		DrawRotaGraph(camera->GetScreenX(shotHitPosX) + SHOT_W, camera->GetScreenY(shotHitPosY), 1.5f, 0, shotHitEff[hitCounter / 2], TRUE, 0);
	//	}
	//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//}
	//else if (shotOccurFlg && hitCounter > 12)
	//{
	//	shotOccurFlg = false;
	//}
}

// チャージ一段階目のエフェクト描画
void Effect::ShotCharge1(Camera * camera, Player *player, Anim * anim)
{
	//if (player->chargeLv1 && effTimer < 30)
	//{
	//	effTimer++;
	//	effCounter = effTimer / 6;
	//	if(effCounter < 5)
	//	{
	//		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	//		DrawRotaGraph(camera->GetScreenX(playerPosX), camera->GetScreenY(playerPosY), 0.5f, 0, shotCharge[effCounter], TRUE);
	//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//	}
	//}

	if (player->chargeLv1 && effTimer < 18)
	{
		effTimer++;
		if (effTimer < 18)
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawRotaGraph(camera->GetScreenX(playerPosX), camera->GetScreenY(playerPosY), 1.0f, 0, shotCharge[effTimer / 3], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

// チャージ二段階目のエフェクト描画
void Effect::ShotCharge2(Camera *camera, Player *player, Anim *anim)
{
	//
	//if (player->chargeLv2 && effTimer < 60)
	//{
	//	effTimer++;
	//	effCounter = effTimer / 6;
	//	if(effCounter > 5 && effCounter < 9)
	//	{
	//		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	//		DrawRotaGraph(camera->GetScreenX(playerPosX), camera->GetScreenY(playerPosY), 1.5f, 0, shotCharge[effCounter - 5], TRUE);
	//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//	}
	//}

	if (player->chargeLv2 && effTimer < 60)
	{
		//effTimer++;
		//effCounter = effTimer / 6;
		//if (effCounter > 5 && effCounter < 9)
		//{
		//	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		//	DrawRotaGraph(camera->GetScreenX(playerPosX), camera->GetScreenY(playerPosY), 1.5f, 0, shotCharge[effCounter - 5], TRUE);
		//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//}

		effCounter++;
		if (effCounter < 18)
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawRotaGraph(camera->GetScreenX(playerPosX), camera->GetScreenY(playerPosY), 1.5f, 0, shotCharge[effCounter / 3], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}
