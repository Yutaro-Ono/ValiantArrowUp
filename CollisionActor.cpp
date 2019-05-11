#include "CollisionActor.h"

// プレーヤーとエネミーの当たり判定処理
void CollisionActor::HitEtoP(Player *player, Enemy *enemy)
{
	//--------------------------------------------------------------//
	// エネミーの画像部位に関する変数
	//-------------------------------------------------------------//
	// エネミーの上端
	float enemyTop	 = enemy->y - ENEMY_H;
	// エネミーの下端
	float enemyUnder = enemy->y + ENEMY_H;
	// エネミーの左端
	float enemyLeft	 = enemy->x - ENEMY_W;
	// エネミーの右端
	float enemyRight = enemy->x + ENEMY_W;
	
	//-------------------------------------------------------------//
	// プレーヤーの画像部位に関する変数
	//------------------------------------------------------------//
	// プレーヤーの上端
	float playerTop   = player->y - PLAYER_H;
	// プレーヤーの下端
	float playerUnder = player->y + PLAYER_H;
	// プレーヤーの左端
	float playerLeft  = player->x - PLAYER_W;
	// プレーヤーの右端
	float playerRight = player->x + PLAYER_W;

	// プレーヤーのダメージフラグが立っていない&&エネミーが死亡していない
	if (!player->damageFlg && !(enemy->hp <= 0))
	{
		// 当たり判定処理メイン
		if ( (playerLeft < enemyLeft  && playerRight > enemyLeft   ||				// プレーヤーの左端がエネミーの左端より小さく、且つプレーヤーの右端がエネミーの右端より小さい　または
			  playerLeft < enemyRight && playerRight > enemyRight) &&				// プレーヤーの左端がエネミーの右端より小さく、且つプレーヤーの右端がエネミーの右端より大きい			(x座標基準)
			 (playerTop  < enemyTop   && playerUnder > enemyTop    ||				// プレーヤーの上端がエネミーの上端より小さく、且つプレーヤーの下端がエネミーの上端より大きい　または
			  playerTop  < enemyUnder && playerUnder > enemyUnder)  )				// プレーヤーの上端がエネミーの下端より小さく、且つプレーヤーの下端がエネミーの下端より大きい			(y座標基準)
		{
			player->damageFlg = true;	// ダメージフラグが立つ
		}
	}
}

void CollisionActor::HitBoss(Player * player, Boss * boss)
{
	//--------------------------------------------------------------//
	// ボスの画像部位に関する変数
	//-------------------------------------------------------------//
	// ボスの上端
	float bossTop = boss->y - ENEMY_BOSS_H;
	// ボスの下端
	float bossUnder = boss->y + ENEMY_BOSS_H;
	// ボスの左端
	float bossLeft = boss->x - ENEMY_BOSS_W;
	// ボスの右端
	float bossRight = boss->x + ENEMY_BOSS_W;

	//-------------------------------------------------------------//
	// プレーヤーの画像部位に関する変数
	//------------------------------------------------------------//
	// プレーヤーの上端
	float playerTop = player->y - PLAYER_H;
	// プレーヤーの下端
	float playerUnder = player->y + PLAYER_H;
	// プレーヤーの左端
	float playerLeft = player->x - PLAYER_W;
	// プレーヤーの右端
	float playerRight = player->x + PLAYER_W;

	// プレーヤーのダメージフラグが立っていない&&ボスが死亡していない
	if (!player->damageFlg && !boss->dieFlg)
	{
		//// 当たり判定処理メイン
		//if ((playerLeft < bossLeft  && playerRight > bossLeft ||				// プレーヤーの左端がエネミーの左端より小さく、且つプレーヤーの右端がエネミーの右端より小さい　または
		//	playerLeft < bossRight && playerRight > bossRight) &&				// プレーヤーの左端がエネミーの右端より小さく、且つプレーヤーの右端がエネミーの右端より大きい			(x座標基準)
		//	(playerTop  < bossTop   && playerUnder > bossTop ||				// プレーヤーの上端がエネミーの上端より小さく、且つプレーヤーの下端がエネミーの上端より大きい　または
		//	playerTop  < bossUnder && playerUnder > bossUnder))				// プレーヤーの上端がエネミーの下端より小さく、且つプレーヤーの下端がエネミーの下端より大きい			(y座標基準)
		if(((playerLeft > bossLeft && playerLeft < bossRight) ||
			(bossLeft > playerLeft && bossLeft < playerRight)) &&
			((playerTop > bossTop && playerTop < bossUnder) ||
			(bossTop > playerTop && bossTop < playerUnder)))
		{
			player->damageFlg = true;	// ダメージフラグが立つ
		}

	}
}

// エネミーと矢の当たり判定
void CollisionActor::HitEnemShot(Enemy *enemy, Shot *shot)
{
	//----------------------------------------------------------------------------------------//
	// エネミーの画像部位に関する変数(*1.5fはエネミー描画の拡大率による)
	//---------------------------------------------------------------------------------------//
	// エネミーの上端
	float enemyTop	 = enemy->y - ENEMY_H * 1.5f;
	// エネミーの下端
	float enemyUnder = enemy->y + ENEMY_H * 1.5f;
	// エネミーの左端
	float enemyLeft	 = enemy->x - ENEMY_W * 1.5f;
	// エネミーの右端
	float enemyRight = enemy->x + ENEMY_W * 1.5f;

	//----------------------------------------------------------------------------------------//
	// ショットの画像部位に関する変数
	//---------------------------------------------------------------------------------------//
	// ショットの上端
	float shotTop   = shot->y - shot->h;
	// ショットの下端
	float shotUnder = shot->y + shot->h;
	// ショットの右端
	float shotRight = shot->x + shot->w;
	// ショットの左端
	float shotLeft  = shot->x - shot->w;

	if(!enemy->dieFlg)
	{ 
		 // 当たり判定処理メイン(矢が可視状態の時)
		if ( !shot->visibleFlg		&&
		   ( shotRight > enemyLeft  && shotRight < enemyRight ||
			 shotLeft  < enemyRight && shotLeft  > enemyLeft) &&
		   ( shotUnder > enemyTop   && shotUnder < enemyUnder ||
			 shotTop   < enemyUnder && shotTop   > enemyTop) )
		{
			enemy->hp -= shot->damage;
			enemy->hitFlg = true;
			shot->hitFlg = true;
		}
		//else
		//{
		//	enemy->hitFlg = false;
		//}
	}
}

void CollisionActor::HitBossShot(Boss * boss, Shot * shot)
{
	//----------------------------------------------------------------------------------------//
	// エネミーの画像部位に関する変数(*1.5fはエネミー描画の拡大率による)
	//---------------------------------------------------------------------------------------//
	// エネミーの上端
	float bossTop = boss->y - ENEMY_BOSS_H;
	// エネミーの下端
	float bossUnder = boss->y + ENEMY_BOSS_H;
	// エネミーの左端
	float bossLeft = boss->x - ENEMY_BOSS_W;
	// エネミーの右端
	float bossRight = boss->x + ENEMY_BOSS_W;

	//----------------------------------------------------------------------------------------//
	// ショットの画像部位に関する変数
	//---------------------------------------------------------------------------------------//
	// ショットの上端
	float shotTop = shot->y - shot->h;
	// ショットの下端
	float shotUnder = shot->y + shot->h;
	// ショットの右端
	float shotRight = shot->x + shot->w;
	// ショットの左端
	float shotLeft = shot->x - shot->w;

	if (!boss->dieFlg)
	{
		// 当たり判定処理メイン(矢が可視状態の時)
		if (!shot->visibleFlg &&
		   (shotRight > bossLeft  && shotRight < bossRight ||
			shotLeft  < bossRight && shotLeft  > bossLeft) &&
		   (shotUnder > bossTop + ENEMY_BOSS_H && shotUnder < bossUnder ||
			shotTop   < bossUnder && shotTop > bossTop + ENEMY_BOSS_H))
		{

			boss->hitBody = true;
			shot->hitFlg = true;
		}
		else if (!shot->visibleFlg &&
			(shotRight > bossLeft + ENEMY_BOSS_W / 2 && shotRight < bossLeft + ENEMY_BOSS_W ||
			shotLeft  < bossLeft + ENEMY_BOSS_W / 2 && shotLeft  > bossLeft + ENEMY_BOSS_W) &&
			(shotUnder > bossTop && shotUnder < bossTop + ENEMY_BOSS_H ||
			shotTop   < bossTop + ENEMY_BOSS_H && shotTop   > bossTop))
		{
			boss->hp -= shot->damage;
			shot->hitFlg = true;
		}

	}
}

void CollisionActor::HitBossLaser(Boss * boss, Player * player)
{
	//----------------------------------------------------------------------------------------//
	// レーザーの画像部位に関する変数(*1.5fはエネミー描画の拡大率による)
	//---------------------------------------------------------------------------------------//
	// レーザーの上端
	float laserTop = boss->tagEffY - BOSS_LASER_H * 3.0f;
	// レーザーの下端
	float laserUnder = boss->tagEffY + BOSS_LASER_H * 3.0f;
	// レーザーの左端
	float laserLeft = boss->tagEffX - BOSS_LASER_W;
	// レーザーの右端
	float laserRight = boss->tagEffX + BOSS_LASER_W;
	

	//-------------------------------------------------------------//
	// プレーヤーの画像部位に関する変数
	//------------------------------------------------------------//
	// プレーヤーの上端
	float playerTop = player->y - PLAYER_H;
	// プレーヤーの下端
	float playerUnder = player->y + PLAYER_H;
	// プレーヤーの左端
	float playerLeft = player->x - PLAYER_W;
	// プレーヤーの右端
	float playerRight = player->x + PLAYER_W;


	if (boss->laserFlg == true)
	{
		if (((playerLeft > laserLeft && playerLeft < laserRight) ||
			(laserLeft > playerLeft && laserLeft < playerRight)) &&
			((playerTop > laserTop && playerTop < laserUnder) ||
			(laserTop > playerTop && laserTop < playerUnder)))
		{
			player->damageFlg = true;	// ダメージフラグが立つ
		}
	}
}

void CollisionActor::HitItem(Player * player, Item * item)
{
	//----------------------------------------------------------------------------------------//
	// アイテムの画像部位に関する変数(*1.5fはエネミー描画の拡大率による)
	//---------------------------------------------------------------------------------------//
	// アイテムの上端
	float itemTop = item->posY;
	// アイテムの下端
	float itemUnder = item->posY + ITEM_H;
	// アイテムの左端
	float itemLeft = item->posX;
	// アイテムの右端
	float itemRight = item->posX + ITEM_W;

	//-------------------------------------------------------------//
	// プレーヤーの画像部位に関する変数
	//------------------------------------------------------------//
	// プレーヤーの上端
	float playerTop = player->y - PLAYER_H;
	// プレーヤーの下端
	float playerUnder = player->y + PLAYER_H;
	// プレーヤーの左端
	float playerLeft = player->x - PLAYER_W;
	// プレーヤーの右端
	float playerRight = player->x + PLAYER_W;

	if (item->visibleFlg == false && item->type == item->TYPE_CURE)
	{
		if (((playerLeft > itemLeft && playerLeft < itemRight) ||
			(itemLeft > playerLeft && itemLeft < playerRight)) &&
			((playerTop > itemTop && playerTop < itemUnder) ||
			(itemTop > playerTop && itemTop < playerUnder)))
		{
			item->hitFlg = true;
		}
	}
}

void CollisionActor::HitShotItem(Shot * shot, Item * item)
{
	//----------------------------------------------------------------------------------------//
	// アイテムの画像部位に関する変数(*1.5fはエネミー描画の拡大率による)
	//---------------------------------------------------------------------------------------//
	// アイテムの上端
	float itemTop = item->posY;
	// アイテムの下端
	float itemUnder = item->posY + ITEM_H;
	// アイテムの左端
	float itemLeft = item->posX;
	// アイテムの右端
	float itemRight = item->posX + ITEM_W;

	//----------------------------------------------------------------------------------------//
	// ショットの画像部位に関する変数
	//---------------------------------------------------------------------------------------//
	// ショットの上端
	float shotTop = shot->y - shot->h;
	// ショットの下端
	float shotUnder = shot->y + shot->h;
	// ショットの右端
	float shotRight = shot->x + shot->w;
	// ショットの左端
	float shotLeft = shot->x - shot->w;

	if (shot->visibleFlg == false && item->visibleFlg == false && item->type == item->TYPE_SCORE &&
		((shotLeft > itemLeft && shotLeft < itemRight) ||
		(itemLeft > shotLeft && itemLeft < shotRight)) &&
		((shotTop > itemTop && shotTop < itemUnder ||
		itemTop > shotTop && itemTop < shotUnder)))
	{
		item->hitFlg = true;
	}


}
