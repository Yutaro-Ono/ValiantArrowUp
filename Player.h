#pragma once
#include "Common.h"
class Camera;
class Map;
class Collision;
class CollisionActor;
class Shot;
class Anim;
class Effect;
class UI;
class Enemy;
class Boss;

class Player
{
public:

	//--------------------------------------------------------------------//
	// 座標関連
	//-------------------------------------------------------------------//
    float           x;		                  // x座標
    float           y;		                  // y座標
    float           velocity;                 // y軸の速度
	// x座標のオフセット
	float			posOffset;

	//--------------------------------------------------------------------//
	// ステータス(体力)関連
	//-------------------------------------------------------------------//
	int				hp;
	int				hpHUD;					// 体力HUD画像格納

	//--------------------------------------------------------------------//
	// アクション関連(ジャンプ・射撃)
	//-------------------------------------------------------------------//
	// ジャンプ処理の際に加わる力
	float			jumpPow;
	// 着地時のY軸合わせに用いるカウント変数
	int				adjustY;
	// 射撃関連
	int				shotInterval;			// ショット毎の間隔(インターバル)
	int				chargeCount;			// チャージ段階のカウント


	//--------------------------------------------------------------------//
	// アニメーション・画像関連
	//-------------------------------------------------------------------//
	// プレーヤーの画像ハンドル
	int				idleGraph;				// 待機状態の画像
	int				moveGraph[6];			// 移動状態の画像(アニメーション)
	int				jumpGraph;				// ジャンプ時に表示する画像
	int				damageGraph;			// 被ダメージ時に表示する画像
	int				shotBowGraph;			// 矢の溜め～発射時用の画像
	// アニメーション用フレームカウンター
	int				moveCount;



	//------------------------------------------------------------------//
	// 効果音(SE)関連
	//-----------------------------------------------------------------//
	int				shotSound;				// 射撃時の効果音
	int				shotHitSound;			// 矢が敵に当たった時の効果音
	int				jumpSound;				// ジャンプ時の効果音
	int				damageSound;			// 被ダメージ時の効果音
	int				footstepSound;			// 足音(着地時に使用)
	int				chargeSound1;			// チャージ1段階目の効果音
	int				chargeSound2;			// チャージ2段階目の効果音

	//------------------------------------------------------------------//
	// フラグ関連
	//-----------------------------------------------------------------//
	// 移動用
	bool			rightMoveFlg;			// 右移動ボタン押下時に立つフラグ
	bool			leftMoveFlg;			// 左移動ボタン押下時に立つフラグ
	// ジャンプアクション用
	bool			jumpFlg;				// ジャンプボタン押下時に立つフラグ
	bool			jumpPushButton;			// ジャンプボタン長押し時にジャンプし続けないようにするためのフラグ
	// 射撃用
	bool			shotFlg;				// ショットボタンを押下した時に立つ
	bool			chargeFlg;				// チャージに移行したときに立つ
	bool			chargeLv0;
	bool			chargeLv1;				// チャージ1段階目
	bool			chargeLv2;				// チャージ2段階目
	// 落下状態の判別
	bool			fallFlg;
	// 被ダメージ時用
	bool			damageFlg;				// プレーヤーがエネミーに当たってダメージを受ける際に立つフラグ
	int				damageCount;			// 被ダメージ時の無敵カウント
	bool			damageFlyFlg;			// 被ダメージ時ふっとんでいるかどうか
	float			damageFlyX;				// 被ダメージ時ふっとび横
	float			damageFlyY;				// 被ダメージ時ふっとび縦
	// 当たり判定用
	bool			hitTopFlg;				// ブロック上の当たり判定フラグ
	bool			hitUnderFlg;			// ブロック下の当たり判定フラグ
	bool			hitLeftFlg;				// ブロック左の当たり判定フラグ
	bool			hitRightFlg;			// ブロック右の当たり判定フラグ
	// 描画用
	int				dirFlg;					// 横の方向( 0 = 右, 1 = 左 )
	bool			stopFlg;				// スクロール時のストップフラグ
	bool			moveFlg;				// 当たり判定に使う移動している or していない フラグ

	//-----------------------------------------------------------//
	// 関数
	//----------------------------------------------------------//
	void	Init();																			// 初期化用関数
	void	Control();																		// 操作処理(移動・ジャンプ・射撃ボタンの押下状態を調べる)
	void	ShotProcess(Camera *camera, Anim *anim, Shot *shot, Effect *effect);			// 
	void	MoveRightX();																	// 右移動のフラグが立った時の詳細な右移動処理
	void	MoveLeftX();																	// 左移動のフラグが立った時の詳細な左移動処理
	void	JumpAction();																	// ジャンプの処理
	void	Gravity();																		// 重力処理
	void	Damage();																		// 被ダメージ処理
	void	HitBlockTop(Map *map, Collision *coll, Camera *camera);							// プレイヤーとマップブロックの当たり判定処理(ブロック上辺)
	void	HitBlockUnder(Map *map, Camera *camera, Collision *coll);						// プレイヤーとマップブロックの当たり判定処理(ブロック下辺)
	void	HitBlockLeft(Map *map, Camera *camera, Collision *coll);						// プレイヤーとマップブロックの当たり判定処理(ブロック左辺)
	void    HitBlockRight(Map *map, Camera *camera, Collision *coll);						// プレイヤーとマップブロックの当たり判定処理(ブロック右辺)
	void	Change();																		// 発射モード処理
	void	Draw(Camera *camera, Shot *shot, Anim *anim);									// 描画
	void	DrawHealth(UI *ui, Camera *camera);												// HPの表示(UI)

};