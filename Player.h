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

//------------------------------------------------------------------//
// プレーヤークラス
//-----------------------------------------------------------------//
// リファクタリング中...
class Player
{
public:

	float				x;						// x座標(プレーヤー)
	float				y;						// y座標(プレーヤー)

	float		velocityY;						// Y軸の速度(ジャンプ時)

	int a;

	// 体力関連
	int            hp;							// 体力(プレーヤー)


    int move = 0;

	 // 発射モード
	int selectShot;			            // 射撃モード選択( 0:通常射撃	1:三本射撃	3:貫通射撃 )

	// ジャンプパワー
	float jumpPow;

	// 着地時のY軸合わせに用いるカウント変数
	int		adjustY;

	//--------------------------------------------------------------------//
	// 画像関連
	//-------------------------------------------------------------------//
	// プレーヤーの画像ハンドル
	int		standGraph;			// プレーヤーの立ち画像格納
	int		moveGraph[6];		// プレーヤーの移動アニメ格納
	int		jumpGraph;			// プレーヤーのジャンプ画像格納
	int		damageGraph;		// プレーヤーのダメージ時画像格納
	int		chargeGraph1;		// プレーヤーの矢発射画像格納(矢を取り出す)
	int		chargeGraph2;		// プレーヤーの矢発射画像格納(矢をつがえる)
	int		chargeGraph3;		// 矢を引き絞る(溜め状態最終)
	int		chargeGraph4;		// 矢の発射

	int            hpHUD;						// プレーヤーの体力表示ウィンドウ
	// x座標のオフセット
	float   posOffset;
	// アニメーション用フレームカウンター
	int		moveCount;

	// 弓関係
	bool	shotFlg;				// ショットボタンを押下した時に立つ
	int		shotInterval;			// ショット毎の間隔(インターバル)
	int		chargeCount;			// チャージ段階のカウント
	bool	chargeFlg;				// チャージに移行したときに立つ
	bool	chargeLv0;
	bool	chargeLv1;				// チャージ1段階目
	bool	chargeLv2;				// チャージ2段階目

	enum ShotMode
	{
		standard,
		triple,
		penetrait
	};

	//------------------------------------------------------------------//
	// SE関連
	//-----------------------------------------------------------------//
	int     hitWallSound;
	int     shotSound;
	int     shotHitSound;
	int     jumpSound;
	int     walkSound;
	int     damageSound;
	int     footstepSound;
	int     chargeSound1;
	int     chargeSound2;

	//------------------------------------------------------------------//
	// フラグ関連
	//-----------------------------------------------------------------//
	// 移動
	bool	rightMoveFlg;			// 右移動ボタン押下時に立つフラグ
	bool	leftMoveFlg;			// 左移動ボタン押下時に立つフラグ
	// ジャンプ
	bool	jumpFlg;				// ジャンプボタン押下時に立つフラグ
	bool	jumpPushButton;			// ジャンプボタン長押し時にジャンプし続けないようにするためのフラグ
	// 落下・重力
	bool	fallFlg;
	// ダメージ
	bool	damageFlg;				// プレーヤーがエネミーに当たってダメージを受ける際に立つフラグ
	int		damageCount;			// 被ダメージ時の無敵カウント
	bool	damageFlyFlg;			// 被ダメージ時ふっとんでいるかどうか
	float	damageFlyX;				// 被ダメージ時ふっとび横
	float	damageFlyY;				// 被ダメージ時ふっとび縦
	// 当たり判定
	bool	hitTopFlg;				// ブロック上の当たり判定フラグ
	bool	hitUnderFlg;			// ブロック下の当たり判定フラグ
	bool	hitLeftFlg;				// ブロック左の当たり判定フラグ
	bool	hitRightFlg;			// ブロック右の当たり判定フラグ
	// 描画
	int		dirFlg;					// 横の方向( 0 = 右, 1 = 左 )
	bool	stopFlg;				// スクロール時のストップフラグ
	bool	moveFlg;				// 当たり判定に使う移動している or していない フラグ


	// 関数群
	void	Init();					// 初期化用関数
	void	Control();				// 操作処理(ボタン押下時のフラグ処理)
	void	ShotProcess(Camera *camera, Anim *anim, Shot *shot, Effect *effect);
	void	MoveRightX();			// 右移動のフラグが立った時の詳細な右移動処理
	void	MoveLeftX();			// 左移動のフラグが立った時の詳細な左移動処理
	void	JumpAction();			
	void	Gravity();
	void	Damage();
	void	HitBlockTop(Map *map, Collision *coll, Camera *camera);
	void	HitBlockUnder(Map *map, Camera *camera, Collision *coll);
	void	HitBlockLeft(Map *map, Camera *camera, Collision *coll);
	void    HitBlockRight(Map *map, Camera *camera, Collision *coll);
	void	Change();				// 発射モード処理
	void	Sound();
	void	Draw(Camera *camera, Shot *shot, Anim *anim);					// 描画
	void	DrawHealth(UI *ui, Camera *camera);

};