#include "Shot.h"

void Shot::Init(Player *player)
{
	x = 0.0f;
	y = 0.0f;
	
	adjustX = player->x;
	adjustY = player->y;

	velocityX = 0.0f;
	velocityY = 0.0f;

	speedMultipl = 0.0f;

	arc = 1.0f;

	count = 0;

	hitFlg = false;

	damage = 1;

	chargeMag = 1;

	remain = SHOT_REMAIN;
	visibleFlg = true;
	shotFlg = false;
	downFlg = false;
	dir = 0;

	LoadDivGraph("data/textures/Effects/Enemy_Hit/EFFECT_SHOT_HIT.png", 6, 5, 2, 192, 192, hitEffect, TRUE);
	hitEffectFlg = false;
	hitCounter = 0;
	effectX = 0.0f;
	effectY = 0.0f;

	hitSound = LoadSoundMem("data/Sound/SE/Shot/ARROW_HIT.mp3");


	graph = LoadGraph("Data/Textures/Weapons/Shot/weapon_arrow.png");
	GetGraphSize(graph, &w, &h);
	w = w / 2;
	h = h / 2;
}

// 弾の発射地点を更新
void Shot::Update(Player *player)
{
	adjustX = player->x;
	adjustY = player->y;
}

// 弾の発射後処理
void Shot::FlyUpdate(Player *player)
{
	if (!visibleFlg)
	{

		if (!dir)
		{
			x += SHOT_SPEED * speedMultipl;
			//y -= velocityY;
			//velocityY -= 0.1f;
		}

		if (dir)
		{
			x -= SHOT_SPEED * speedMultipl;
			//y -= velocityY;
			//velocityY -= 0.1f;
		}

	}
	// 弾が見えてない時、プレーヤーの座標と向きに合わせ、矢が敵にヒットしていないことにする
	if (visibleFlg)
	{

		shotFlg = false;
		if (player->dirFlg == 0)
		{
			// 矢の座標をプレーヤーに合わせる(+wと+hは適切な射出位置に合わせるための調整用)
			x = adjustX;
			y = adjustY;
			// 矢の向き(dir)もプレーヤーに合わせる
			dir = player->dirFlg;
		}

		if (player->dirFlg == 1)
		{
			// 矢の座標をプレーヤーに合わせる(+wと+hは適切な射出位置に合わせるための調整用)
			x = adjustX;
			y = adjustY;
			// 矢の向き(dir)もプレーヤーに合わせる
			dir = player->dirFlg;
		}

		//// 矢の座標をプレーヤーに合わせる(+wと+hは適切な射出位置に合わせるための調整用)
		//x = adjustX + w;
		//y = adjustY + h / 2;
		//// 矢の向き(dir)もプレーヤーに合わせる
		//dir = player->dirFlg;
	}

	if (shotFlg)
	{

	}

}

// 画面外に出た時矢を消す
void Shot::EraseOut(Camera * camera, Player * player)
{
    if (dir == false && player->x - x > 960)
    {
        visibleFlg = true;
    }
    if (dir == true && player->x - x < -960)
    {
        visibleFlg = true;
    }
}

// 弾のエネミーに対する当たり判定処理
void Shot::HitEnemy(Camera *camera, Anim *anim, Enemy *enemy, Effect *effect)
{
	if (hitFlg)
	{
		// ダメージを1に戻す
		damage = 1;
		velocityY = 0.0f;

		// 着弾時エフェクトフラグとカウント
		//effect->hitCounter = 0;
		//effect->shotOccurFlg = true;


		// エフェクト処理
		effectX = x;		// エフェクトの発生地点(x座標を更新)
		effectY = y;		// エフェクトの発生地点(y座標を更新)
		hitCounter = 0;
		hitEffectFlg = true;

		// ヒット効果音
		PlaySoundMem(hitSound, DX_PLAYTYPE_BACK);

		visibleFlg = true;
		hitFlg = false;
	}
}

// 弾のブロックに対する当たり判定処理
void Shot::HitBlock(Map *map, Collision *coll, Player *player)
{
	if (!visibleFlg)
	{
		if (coll->CheckHitTop(map, x, y, w, h) ||
			coll->CheckHitUnder(map, x, y, w, h) ||
			coll->CheckHitRight(map, x, y, w, h) ||
			coll->CheckHitLeft(map, x, y, w, h))
		{
			visibleFlg = true;
			// ダメージを1に戻す
			damage = 1;

			velocityY = 0.0f;
		}
	}
}

void Shot::Draw(Camera *camera, Player *player)
{
	if (!visibleFlg)
	{
		DrawRotaGraph(camera->GetScreenX(x), camera->GetScreenY(y), 1.0f, 0, graph, TRUE, dir);
	}
}

void Shot::DrawHitEffect(Camera * camera)
{
	// エフェクトの合図が出たらカウント開始し、一定時間後エフェクトを消す
	if (hitEffectFlg && hitCounter <= 10)
	{

		hitCounter++;

		// エフェクトの描画メイン
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		if (dir == true)
		{
			DrawRotaGraph(camera->GetScreenX(effectX) - SHOT_W, camera->GetScreenY(effectY), 1.5f, 0, hitEffect[hitCounter / 2], TRUE, 0);
		}
		if (dir == false)
		{
			DrawRotaGraph(camera->GetScreenX(effectX) + SHOT_W, camera->GetScreenY(effectY), 1.5f, 0, hitEffect[hitCounter / 2], TRUE, 0);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (hitEffectFlg && hitCounter > 12)
	{
		hitEffectFlg = false;
	}
}
