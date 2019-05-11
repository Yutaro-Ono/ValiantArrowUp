#include "EnemyBoss.h"

void Boss::Init()
{
	LoadDivGraph("data/textures/actors/enemies/Enemy_ForestShadow.png", 6, 6, 1, ENEMY_BOSS_W * 2, ENEMY_BOSS_H * 2, graph, TRUE);
	standGraph = LoadGraph("data/textures/actors/enemies/Enemy_ForestShadow_Stand.png", TRUE);
	LoadDivGraph("data/textures/Effects/Boss/BOSS_EFFECT_SHIELD.png", 10, 5, 2, 240, 240, shieldEffect, TRUE);
	state = STATE_FREEZE;

	x = 15000.0f;
	y = 740.0f;

	hp = 25;

	dir = true;

	moveDirection = false;
	changeDirection = false;
	moveFlg = false;
	dieFlg = false;

	moveCount = 0;

	hitBody = false;
	hitCount = 0;
	hitWeak = false;

	targetTimer = 0;
	targetCount = 0;
	targetFlg = false;
	LoadDivGraph("data/textures/Effects/Boss/BOSS_EFFECT_TARGET.png", 6, 2, 3, 384, 384, tagEff, TRUE);
	LoadDivGraph("data/textures/Effects/Boss/BOSS_EFFECT_CHARGE.png", 10, 10, 1, 240, 240, tagChargeEff, TRUE);
	tagEffX = 0.0f;
	tagEffY = 950.0f;

	LoadDivGraph("data/textures/Effects/Boss/BOSS_EFFECT_SHOT.png", 6, 2, 3, 384, 384, laserFlash, TRUE);
	LoadDivGraph("data/textures/Effects/Boss/BOSS_EFFECT_LASER.png", 6, 2, 3, 384, 384, laserGraph, TRUE);
	
	chargeSound = LoadSoundMem("data/Sound/SE/Boss/BOSS_CHARGE.mp3");
	flashSound = LoadSoundMem("data/Sound/SE/Boss/BOSS_FLASH.mp3");
	footstepSound = LoadSoundMem("data/Sound/SE/Boss/BOSS_FOOTSTEP.mp3");
	shieldSound = LoadSoundMem("data/Sound/SE/Boss/BOSS_SHIELD.mp3");
	laserSound = LoadSoundMem("data/Sound/SE/Boss/BOSS_LASER.mp3");
	flashFlg = false;
	laserFlg = false;
	flashCounter = 0;
	laserTimer = 0;
	laserCount = 0;

	animCounter = 0;
}

void Boss::Routine(Player * player)
{

	if (hp <= 0)
	{
		state = STATE_DEATH;
	}


	if (state == STATE_FREEZE)
	{

		// プレーヤーが一定以上近づいたら動き出す
		if ((x - player->x) < 1000)
		{
			state = STATE_MOVE;
		}
	}
	// 移動状態
	if (state == STATE_MOVE)
	{
		laserFlg = false;
		// 移動の回数を制御するカウンターを回す
		moveCount++;

		// 進行方向変更
		while (changeDirection == false)
		{
			if (moveDirection == false)
			{
				moveDirection = true;
				changeDirection = true;
				break;
			}
			if (moveDirection == true)
			{
				moveDirection = false;
				changeDirection = true;
				break;
			}
		}

		// 前方に進む時
		if (moveDirection == false && moveCount % 50 == 0)
		{
			x += BOSS_SPEED;
			// 効果音
			PlaySoundMem(footstepSound, DX_PLAYTYPE_BACK);
		}
		// 後方に進む時
		if (moveDirection == true && moveCount % 50 == 0)
		{
			x -= BOSS_SPEED;
			PlaySoundMem(footstepSound, DX_PLAYTYPE_BACK);
		}

		tagEffY = 950;

		// カウントが一定以上になったらターゲット状態へ移行
		if (moveCount >= 300)
		{

			state = STATE_TARGET;
		}
	}

	if (state == STATE_TARGET)
	{
		// ターゲットフラグがオフの時(最初の一回のみ)、現在時刻をタイマーに記録
		if (targetFlg == false)
		{
			moveCount = 0;
			targetTimer = GetNowCount();
			// 初期化
			changeDirection = false;

			targetFlg = true;
		}

		// ターゲット状態に入った時点から何秒経ったかをカウントに代入
		targetCount = (GetNowCount() - targetTimer) / 1000;

		tagEffX = player->x;

		// 効果音再生
		if (!CheckSoundMem(chargeSound))
		{
			PlaySoundMem(chargeSound, DX_PLAYTYPE_BACK);
		}


		// 5秒経過後、アタックステートへ移行
		if (targetCount == 5)
		{
			targetFlg = false;
			state = STATE_ATTACK;
		}
	}

	if (state == STATE_ATTACK)
	{
		// アタック状態に入ったとき
		if (flashFlg == false && laserFlg == false)
		{
			flashFlg = true;
		}

		// フラッシュフラグが立ったら
		if (flashFlg == true)
		{
			flashCounter++;
			// 効果音
			if (!CheckSoundMem(laserSound))
			{
				PlaySoundMem(laserSound, DX_PLAYTYPE_BACK);
			}
			if (flashCounter == 70)
			{
				laserTimer = GetNowCount();
				laserFlg = true;
				flashFlg = false;
			}
		}

		if (laserFlg == true)
		{
			laserCount = (GetNowCount() - laserTimer) / 1000;

			if (laserCount >= 4)
			{
				flashCounter = 0;
				state = STATE_MOVE;
			}

		}
	}

	if (state == STATE_DEATH)
	{
		dieFlg = true;
	}
}

void Boss::HitShotBody()
{
	if (!hitBody)
	{
		hitCount = 0;
	}
	
	// 矢に当たったら
	if (hitBody)
	{
		// 効果音
		if (hitCount == 0)
		{
			PlaySoundMem(shieldSound, DX_PLAYTYPE_BACK);
		}
		hitCount++;

		if (hitCount == 46)
		{
			hitBody = false;
		}
	}
}

void Boss::Damage()
{
	if (hitWeak)
	{
		
	}
}

void Boss::Draw(Anim * anim, Camera * camera)
{
	animCounter++;

	// ボス描画メイン
	if (targetFlg == true)
	{
		DrawRotaGraph(camera->GetScreenX(x), camera->GetScreenY(y), 1.0f, 0, standGraph, TRUE, dir);
	}
	else
	{
		DrawRotaGraph(camera->GetScreenX(x), camera->GetScreenY(y), 1.0f, 0, graph[moveCount / 50], TRUE, dir);
	}
	
	
	
	if (animCounter >= 600)
	{
		animCounter = 0;
	}
}

void Boss::DrawEffect(Anim * anim, Camera * camera)
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	// ターゲット時追尾エフェクト描画
	if (targetFlg == true)
	{
		DrawRotaGraph(camera->GetScreenX(tagEffX), camera->GetScreenY(tagEffY), 1, 0, tagEff[anim->counter], TRUE);
		DrawRotaGraph(camera->GetScreenX(x - 150), camera->GetScreenY(y - 150), 1, 0, tagChargeEff[anim->counter], TRUE);
	}

	if (flashFlg == true)
	{
		DrawRotaGraph(camera->GetScreenX(x - 150), camera->GetScreenY(y - 150), 1, 0, laserFlash[(60 - flashCounter - 10) / 10], TRUE);
	}

	if (laserFlg == true)
	{
		DrawRotaGraph(camera->GetScreenX(tagEffX), camera->GetScreenY(tagEffY -= 1), 3, 0, laserGraph[5 - anim->counter], TRUE);
	}

	if (hitBody == true)
	{
		DrawRotaGraph(camera->GetScreenX(x), camera->GetScreenY(y), 2.0f, 0, shieldEffect[hitCount / 5], TRUE, dir);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
