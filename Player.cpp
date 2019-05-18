#include "Player.h"

//------------------------------------------------//
// プレーヤーの初期化
//-----------------------------------------------//
void Player::Init()
{
	// 画像ファイル(.png)のロード
	hpHUD = LoadGraph("Data/Interface/HUD/HUD_HP_BAR_2.png");
	idleGraph = LoadGraph("data/textures/actors/player/player_stand.png");
	LoadDivGraph("data/textures/actors/player/player_walk.png", 6, 6, 1, PLAYER_W * 2, PLAYER_H * 2, moveGraph, TRUE);
	damageGraph = LoadGraph("data/textures/actors/player/player_damage.png");
	shotBowGraph = LoadGraph("data/textures/actors/player/player_shot4.png");
	// 音楽ファイル(.mp3)のロード
	jumpSound = LoadSoundMem("data/Sound/SE/Player/PLAYER_JUMP.mp3");
	damageSound = LoadSoundMem("data/Sound/SE/Player/PLAYER_DAMAGE.mp3");
	footstepSound = LoadSoundMem("data/Sound/SE/Player/PLAYER_FOOTSTEP.mp3");
	shotSound = LoadSoundMem("data/Sound/SE/Shot/ARROW_SHOT.mp3");
	chargeSound1 = LoadSoundMem("data/Sound/SE/Player/PLAYER_CHARGE_2.mp3");
	chargeSound2 = LoadSoundMem("data/Sound/SE/Player/PLAYER_CHARGE.mp3");

	// プレイヤー座標の初期化
	x = 512.0f;
	y = 890.0f;

	// 重力
	velocityY = 9.0f;

	hp = PLAYER_MAX_LIFE;

	// ジャンプ
	jumpPow = -16.0f;

	posOffset = x;

	// 弓関係
	shotFlg = false;
	shotInterval = 0;

	chargeFlg = false;
	chargeCount = 0;
	chargeLv0 = false;
	chargeLv1 = false;
	chargeLv2 = false;

	// 着地時Y軸調整カウント用
	adjustY = 0;

	// 移動用フラグ
	rightMoveFlg = false;
	leftMoveFlg = false;
	// ジャンプフラグ
	jumpFlg = false;
	jumpPushButton = false;
	// 落下フラグ
	fallFlg = true;
	// ダメージ関係
	damageFlg = false;
	damageCount = 0;
	damageFlyFlg = false;
	damageFlyX = 0.0f;
	damageFlyY = 0.0f;
	// 当たり判定用フラグ群
	hitTopFlg = false;
	hitUnderFlg = false;
	hitLeftFlg = false;
	hitRightFlg = false;

	// 向きフラグ
	dirFlg = 0;
	stopFlg = false;
	moveFlg = false;
}

//------------------------------------------------//
// プレーヤーの操作処理
//-----------------------------------------------//
void Player::Control()
{
	// 右移動
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		dirFlg = 0;
		rightMoveFlg = true;
		leftMoveFlg = false;
		moveFlg = true;
	}
	else
	{
		rightMoveFlg = false;
	}

	// 左移動
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		dirFlg = 1;
		leftMoveFlg = true;
		rightMoveFlg = false;
		moveFlg = true;
	}
	else 
	{
		leftMoveFlg = false;
	}
	
	// どちらも押されていない時
	if (!(CheckHitKey(KEY_INPUT_LEFT)) && !(CheckHitKey(KEY_INPUT_RIGHT)))
	{
		moveFlg = false;
	}

	// ジャンプ時処理
	if (CheckHitKey(KEY_INPUT_SPACE) && !jumpFlg && !chargeFlg && !hitUnderFlg && !fallFlg && !jumpPushButton)
	{
		jumpFlg = true;
		// ジャンプ効果音
		if (jumpPushButton == false)
		{
			PlaySoundMem(jumpSound, DX_PLAYTYPE_BACK);
		}
		jumpPushButton = true;
		velocityY = jumpPow;
	}
	// ボタンを離したらジャンプボタンを押し続けているかどうかのフラグをオフ
	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && jumpPushButton)
	{
		jumpPushButton = false;
	}

	// インターバル中でない時、もしショットボタンが押されたらチャージを開始
	if (CheckHitKey(KEY_INPUT_B) && shotFlg == false)
	{
		chargeFlg = true;
		chargeCount++;

		// チャージ状態の遷移
		if (chargeCount < 30)
		{
			chargeLv0 = true;
		}
		// チャージの段階処理
		if (chargeCount >= 30)
		{
			if (chargeCount == 30)
			{
				PlaySoundMem(chargeSound1, DX_PLAYTYPE_BACK);
			}
			chargeLv0 = false;
			chargeLv1 = true;
		}
		if (chargeCount >= 60)
		{
			if (chargeCount == 60)
			{
				PlaySoundMem(chargeSound2, DX_PLAYTYPE_BACK);
			}
			chargeLv1 = false;
			chargeLv2 = true;
		}

	}
	// ショットのインターバル処理
	if (shotFlg == true)
	{
		shotInterval++;
		if (shotInterval == 30)
		{
			shotFlg = false;
		}
	}

}

// 射撃処理
void Player::ShotProcess(Camera *camera, Anim *anim, Shot *shot, Effect *effect)
{
	// ショットボタンが離されたら発射し、初期化
	if (chargeFlg && !CheckHitKey(KEY_INPUT_B))
	{

		// 発射前に速度とダメージを格納
		if (chargeLv0)
		{
			shot->damage = 1;
			shot->speedMultipl = 0.5f;
			shot->chargeMag = 3;
			shot->velocityY = shot->arc * shot->chargeMag;
		}
		if (chargeLv1)
		{
			shot->damage = 3;
			shot->speedMultipl = 1.0f;
			shot->chargeMag = 3;
			shot->velocityY = shot->arc * shot->chargeMag;
		}
		if (chargeLv2)
		{
			shot->damage = 5;
			shot->speedMultipl = 1.5f;
			shot->chargeMag = 3;
			shot->velocityY = shot->arc * shot->chargeMag;
		}

		shot->visibleFlg = false;

		if (shotFlg == false)
		{
			PlaySoundMem(shotSound, DX_PLAYTYPE_BACK);
		}

		// 発射処理
		shotFlg = true;
		shot->shotFlg = true;

		chargeCount = 0;

		chargeLv0 = false;
		chargeLv1 = false;
		chargeLv2 = false;

		shotInterval = 0;

		chargeFlg = false;

	}
}

//------------------------------------------------------//
// プレーヤーのアクション(移動関係)処理
//-----------------------------------------------------//
// プレーヤー右移動処理
void Player::MoveRightX()
{
	if (rightMoveFlg && moveFlg && !chargeFlg)
	{
		x += PLAYER_SPEED;
	}
}
// プレーヤー左移動処理
void Player::MoveLeftX()
{
	if (leftMoveFlg && moveFlg && !chargeFlg)
	{
		x -= PLAYER_SPEED;
	}
}
// プレーヤーのジャンプ処理
void Player::JumpAction()
{
	if (jumpFlg)
	{
		y += velocityY;
		velocityY += 0.5f;
	}
}

// プレーヤーの重力処理
void Player::Gravity()
{
	// ジャンプ時以外は常時重力がかかり続ける
	if (!jumpFlg)
	{
		y += GRAVITY_ALL;
	}
}

// 被ダメージ時処理
void Player::Damage()
{
	// ダメージフラグが立っていないとき初期化
	if (!damageFlg)
	{
		damageFlyX = PLAYER_DAMAGE_FLY_X;
		damageFlyY = PLAYER_DAMAGE_FLY_Y;

		damageCount = 0;
	}

	// ダメージフラグが立ったらプレーヤーを吹き飛ばし、2秒後にダメージフラグ解除
	if (damageFlg)
	{
		// 一度だけ体力を減らし効果音を鳴らす
		if (damageCount == 0)
		{
			hp -= 1;
			PlaySoundMem(damageSound, DX_PLAYTYPE_BACK);
		}
		damageCount++;

		// 一度だけ吹き飛ばしフラグをオン
		if (damageFlyY == PLAYER_DAMAGE_FLY_Y)
		{
			damageFlyFlg = true;
		}

		// 吹き飛ばし処理メイン(dir == 0 なら右へ、dir == 1 なら左へ飛ぶ)
		if (dirFlg)
		{
			if (damageFlyFlg && damageFlyY <= 0)
			{
				x += damageFlyX;
				// ジャンプしていない時のみ上へ飛ばす
				if (!jumpFlg)
				{
					y += damageFlyY;

					damageFlyY += 1;
				}

			}
		}
		if (!dirFlg)
		{
			if (damageFlyFlg && damageFlyY <= 0)
			{
				x -= damageFlyX;

				// ジャンプしていない時のみ上へ飛ばす
				if (!jumpFlg)
				{
					y += damageFlyY;

					damageFlyY += 1;
				}

			}
		}
		
		if (damageFlyY == 0)
		{
			damageFlyFlg = false;
		}
		
		// 一定時間後に無敵解除
		if (damageCount > 120)
		{
			damageFlg = false;
		}

		//// カウント開始
		//damageCount++;
		//// 一定時間後に無敵解除
		//if (damageCount > 120)
		//{
		//	damageFlg = false;
		//}
	}
}

//-----------------------------------------------------------------------//
// 当たり判定処理
//----------------------------------------------------------------------//
// プレーヤーのブロック上部当たり判定処理
void Player::HitBlockTop(Map *map, Collision *coll, Camera *camera)
{
	// Collision内の上部当たり判定をジャッジする関数に、当たっているか否かのboolを返してもらう
	hitTopFlg = coll->CheckHitTop(map, x, y, PLAYER_W - PLAYER_W / 2, PLAYER_H);

	if (hitTopFlg)
	{
		// ブロック上部にプレーヤーを押し戻す
		y = map->GetNumY(y) * MAP_SIZE + PLAYER_H / 1.5f;

		// 接地しているため空中関係のフラグをオフに
		jumpFlg = false;

		// 着地音再生
		if (fallFlg == true && !CheckSoundMem(footstepSound))
		{
			PlaySoundMem(footstepSound, DX_PLAYTYPE_BACK);
		}

		fallFlg = false;
	}
	else
	{
		// 接地していない場合落下する
		fallFlg = true;
	}
}

// プレーヤーのブロック底部当たり判定処理
void Player::HitBlockUnder(Map *map, Camera *camera, Collision *coll)
{
	hitUnderFlg = coll->CheckHitUnder(map, x, y, PLAYER_W, PLAYER_H);

	if (hitUnderFlg)
	{
		jumpFlg = false;
	}
}

// プレーヤーのブロック左側当たり判定処理
void Player::HitBlockLeft(Map *map, Camera *camera, Collision *coll)
{
	hitLeftFlg = coll->CheckHitLeft(map, x, y, PLAYER_W, PLAYER_H);

	if (hitLeftFlg)
	{
		x -= PLAYER_SPEED;	
	}

}

// プレーヤーのブロック右側当たり判定処理
void Player::HitBlockRight(Map *map, Camera *camera, Collision *coll)
{
	hitRightFlg = coll->CheckHitRight(map, x, y, PLAYER_W, PLAYER_H);

	if (hitRightFlg)
	{
		x += PLAYER_SPEED;
	}
}

//------------------------------------------------//
// プレーヤーの描画処理
//-----------------------------------------------//
void Player::Draw(Camera *camera, Shot *shot, Anim *anim)
{
	if(damageFlg == FALSE || damageFlg == TRUE && damageCount % 25 / 8)
	{
		// 待機時の描画
		if (!moveFlg && !chargeFlg && !jumpFlg)
		{
			DrawRotaGraph(camera->GetScreenX(x), camera->GetScreenY(y), 1.0f, 0, idleGraph, TRUE, dirFlg);
		}

		// 移動時の描画
		if (moveFlg && !chargeFlg && !jumpFlg)
		{
			DrawRotaGraph(camera->GetScreenX(x), camera->GetScreenY(y), 1.0f, 0, moveGraph[anim->counter], TRUE, dirFlg);
		}

		// ジャンプ時の描画
		if (jumpFlg && !chargeFlg)
		{
			DrawRotaGraph(camera->GetScreenX(x), camera->GetScreenY(y), 1.0f, 0, damageGraph, TRUE, dirFlg);
		}

		if (chargeFlg)
		{
			DrawRotaGraph(camera->GetScreenX(x), camera->GetScreenY(y), 1.0f, 0, shotBowGraph, TRUE, dirFlg);
		}
	}

	//// 体力表示(仮)
	//DrawFormatString(camera->GetScreenX(x - PLAYER_W / 2), camera->GetScreenY(y - PLAYER_H * 2), GetColor(255, 0, 0), "HP:%d", hp);
}

void Player::DrawHealth(UI * ui, Camera *camera)
{
	//DrawGraph(640, 5, hpHUD, TRUE);
	//DrawBox(724, 33, 1196, 148, GetColor(255, 0, 0), TRUE);
}
