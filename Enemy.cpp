#include "Enemy.h"

//------------------------------------------------//
// エネミーの初期化
//-----------------------------------------------//
void Enemy::Init()
{

	hp = 2;

	dir = false;

	manager = STATE_MOVE;

	moveFlg = false;

	moveRight = false;
	moveLeft = false;

	dieFlg = false;

	fallFlg = true;

	hitFlg = false;
	damageFlg = false;
	damageCounter = 0;
	damageFlyDist = 0.0f;
	damageVelocity = 0.0f;

	// ハーピー用フラグ
	upDown = true;
	maxFly = 0;

	// 当たり判定用フラグ
	hitTop = false;
	hitUnder = false;
	hitRight = false;
	hitLeft = false;

}

//------------------------------------------------//
// エネミーのupdate
//-----------------------------------------------//
void Enemy::Update()
{
	
}

// エネミーの移動ルーチン
void Enemy::MoveRoutine(int i)
{
	// 移動状態のモッフ
	if(manager == STATE_MOVE && ((i % 2) == 0))
	{
		// 被ダメージ時かつ死亡時以外は移動し続ける
		if(!damageFlg && !dieFlg)
		{
			// 右方向移動
			if (moveRight)
			{
				moveFlg = true;
				dir = false;
				x += ENEMY_SPEED;
			}
			// 左方向移動
			else if (moveLeft)
			{
				moveFlg = true;
				dir = true;
				x -= ENEMY_SPEED;
			}
			// 移動方向をランダムに設定(開始時一度のみ)
			else if(hitTop)
			{
				if (i % 3)
				{
					moveRight = true;
				}
				else
				{
					moveLeft = true;
				}
			}
		}
	}
	
	// 移動状態のハーピー
	if (manager == STATE_MOVE && (i % 2 == 1))
	{
		dir = true;
		// 上移動
		if (upDown)
		{
			y -= ENEMY_HARPY_FLY;
			maxFly -= ENEMY_HARPY_FLY;
			// 一定以上上へ飛んだら、下方向へ反転
			if (maxFly < -150)
			{
				upDown = false;
			}
		}
		// 下移動
		if (!upDown)
		{
			y += ENEMY_HARPY_FLY;
			maxFly += ENEMY_HARPY_FLY;
			// 一定以上下へ飛んだら、上方向へ反転
			if (maxFly > 150)
			{
				upDown = true;
			}
		}
		if (hp <= 0)
		{
			y += GRAVITY_ALL;
		}
	}

}

// エネミーの被ダメージ時リアクション
void Enemy::DamageReaction(Player * player, int i)
{
	// モッフ当たり判定
	if((i % 2) == 0)
	{
		// 矢に当たったら
		if (hitFlg)
		{
			if (x > player->x)
			{
				damageFlyDist = ENEMY_FLY;
			}
			if (x < player->x)
			{
				damageFlyDist = -ENEMY_FLY;
			}
			damageVelocity = -20.0f;
			damageCounter = 0;


			// 最後にダメージフラグを立てる
			damageFlg = true;
			manager = STATE_ATTACK;
			hitFlg = false;
		}

		if(damageFlg)
		{
			if (x > player->x && damageVelocity < 0)
			{
				x += damageFlyDist;
				y += damageVelocity;
				damageVelocity += 0.5f;
			}
			if (x < player->x && damageVelocity < 0)
			{
				x += damageFlyDist;
				y += damageVelocity;
				damageVelocity += 0.5f;
			}

			damageCounter++;
			// 被ダメージフラグをオフ
			if (damageCounter > 120)
			{
				damageFlg = false;
			}
		}
	}

	// ハーピー当たり判定
	if ((i % 2) == 1)
	{
		if (hitFlg)
		{
			damageFlg = true;
			hitFlg = false;
		}

		if (damageFlg)
		{
			damageCounter++;
			// 被ダメージフラグをオフ
			if (damageCounter > 120)
			{
				damageFlg = false;
			}
		}
	}
}

// エネミー追尾ルーチン
void Enemy::TrackRoutine(Player *player)
{
	// ダメージを受けた時プレーヤーを追尾する
	if(manager == STATE_ATTACK)
	{
		if(!dieFlg)
		{
			moveFlg = true;

			if (player->x > x)
			{
				dir = false;
				x += ENEMY_SPEED * 2;
			}
			if (player->x < x)
			{
				dir = true;
				x -= ENEMY_SPEED * 2;
			}
		}
		else
		{
			moveFlg = false;
		}

		// プレーヤーと一定距離離れたら通常の移動に戻る
		if (player->x - x > 960 || player->x - x < -960)
		{
			manager = STATE_MOVE;
		}

		// プレーヤーが上のブロックへ避難していたら通常の移動に戻る
		if (x == player->x && y - player->y > 32 && player->hitTopFlg == true)
		{
			manager = STATE_MOVE;
		}
	}
}

// エネミー死亡時
void Enemy::Died(UI *ui)
{
	if(hp <= 0)
	{
		if(y >= 1080)
		{
			if (dieFlg == false)
			{
				ui->AddScore(1);
			}
			dieFlg = true;
		}
	}
}

// 重力処理
void Enemy::Gravity(int i)
{
	if (fallFlg && (i % 2) == 0)
	{
		y += GRAVITY_ALL;
	}
}

// 一個先のブロックが存在しているかどうかを検出し、エネミーの移動方向を反転
void Enemy::HitBlockVoid(Collision * coll, Map * map)
{
	// 右に移動している&&落下中でない
	if (moveRight && !fallFlg)
	{
		if(coll->CheckHitTop(map, x + ENEMY_W, y, ENEMY_W, ENEMY_H + ENEMY_H / 2) == 0)
		{
			moveLeft = true;
			moveRight = false;
		}
	}
	// 左に移動している&&落下中でない
	else if (moveLeft && !fallFlg)
	{
		if(coll->CheckHitTop(map, x - ENEMY_W, y, ENEMY_W, ENEMY_H + ENEMY_H / 2) == 0)
		{
			moveRight = true;
			moveLeft = false;
		}
	}
}

// ブロック上部に当たった(エネミーが接地した)時の処理
void Enemy::HitBlockTop(Camera *camera, Collision *coll, Map *map)
{

	if(hp > 0)
	{
		hitTop = coll->CheckHitTop(map, x, y, ENEMY_W, ENEMY_H + ENEMY_H / 2);
	}
	else
	{
		hitTop = false;
	}
	
	if (hitTop)
	{
		// ブロック上部にエネミーを押し戻す
		y = map->GetNumY(y) * MAP_SIZE + PLAYER_H / 1.5f;
		fallFlg = false;
	}
	if (!hitTop)
	{
		fallFlg = true;
	}

}

// ブロック底面に当たった(エネミーの上側が当たった)時の処理
void Enemy::HitBlockUnder(Camera *camera, Collision *coll, Map *map)
{
	hitUnder = coll->CheckHitUnder(map, x, y, ENEMY_W, ENEMY_H);

	if (hitUnder)
	{

	}
}

// ブロック右側に当たった(エネミーの左側が壁に当たった)時の処理 ※if文の && hp > 0 はエネミーが死亡していないということを意味する
void Enemy::HitBlockRight(Camera *camera, Collision *coll, Map *map, Player * player)
{
	if (manager == STATE_MOVE && !damageFlg && hp > 0)
	{
		hitRight = coll->CheckHitRight(map, x, y, ENEMY_W, ENEMY_H);
	}
	// ダメージを受けて吹っ飛んでいるとき壁に埋まらないようにするための処理
	if (damageFlg && hp > 0)
	{
		hitRight = coll->CheckHitRight(map, x + damageFlyDist, y, ENEMY_W, ENEMY_H);

		if (hitRight)
		{
			x -= damageFlyDist;
		}
	}

	// アタックステート時の当たり判定(普段より高速で動いているため)
	if (manager == STATE_ATTACK && hp > 0)
	{
		hitRight = coll->CheckHitRight(map, x - ENEMY_SPEED * 2, y, ENEMY_W, ENEMY_H);
		if (hitRight)
		{
			x += ENEMY_SPEED * 2;

			// 攻撃状態を解除
			if (y - player->y > 64 && player->hitTopFlg == true)
			{
				manager = STATE_MOVE;
			}

		}
	}

	if (hitRight)
	{
		moveRight = true;
		moveLeft = false;
	}
	if (!hitRight)
	{

	}
}

// ブロック左側に当たった(エネミーの右側が壁に当たった)時の処理
void Enemy::HitBlockLeft(Camera *camera, Collision *coll, Map *map, Player * player)
{
	
	if (manager == STATE_MOVE && !damageFlg && hp > 0)
	{
		hitLeft = coll->CheckHitLeft(map, x, y, ENEMY_W, ENEMY_H);
	}
	// ダメージを受けて吹っ飛んでいるとき壁に埋まらないようにするための処理
	if (damageFlg && hp > 0)
	{
		hitLeft = coll->CheckHitLeft(map, x + damageFlyDist, y, ENEMY_W, ENEMY_H);

		if (hitLeft)
		{
			x -= damageFlyDist;
		}
	}

	// アタックステート時の当たり判定処理
	if (manager == STATE_ATTACK && hp > 0)
	{
		hitLeft = coll->CheckHitLeft(map, x + ENEMY_SPEED * 2, y, ENEMY_W, ENEMY_H);
		if (hitLeft)
		{
			x -= ENEMY_SPEED * 2;

			// 壁にぶつかった時、プレーヤーが上のブロックに立っていたら攻撃状態を解除
			if (y - player->y > 64 && player->hitTopFlg == true)
			{
				manager = STATE_MOVE;
			}

		}
	}


	if (hitLeft)
	{
		moveLeft = true;
		moveRight = false;
	}
	if (!hitLeft)
	{

	}
}

//------------------------------------------------//
// エネミーの描画
//-----------------------------------------------//
void Enemy::Draw(Camera *camera, Anim *anim, UI *ui)
{
	if(!dieFlg)
	{
		ui->HealthBar(camera, x, y, ENEMY_W / 1.5f, ENEMY_H * 1.5f, ENEMY_LIFE * 2, hp * 2);
	}
}