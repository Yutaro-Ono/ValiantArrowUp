#pragma once

#include "DxLib.h"
// ゲームシーン
#include "GameScene.h"
// カメラ
#include "Camera.h"
// 当たり判定
#include "Collision.h"
#include "CollisionActor.h"
// プレーヤー
#include "Player.h"
// エネミー
#include "Enemy.h"
#include "EnemyBoss.h"
#include "EnemyLegion.h"
// ショット
#include "Shot.h"
// マップ
#include "Map.h"
// アイテム
#include "Item.h"
// 背景
#include "BgImage.h"
// エフェクト
#include "Effect.h"
// 音楽
#include "SoundManager.h"
// UI
#include "Interface.h"
// bitmapフォント
//#include "bitmapText.h"
// アニメーション
#include "AnimCounter.h"
// デバッグ
#include "Debug.h"

//class Anim;
//class Camera;
//class Map;
//class Collision;
//class Boss;
//class Shot;
//class Effect;
//class UI;
//class Player;
//class Boss;

// 画面サイズ
#define SCREEN_W 1920
#define SCREEN_H 1080

// 重力設定
#define GRAVITY_ALL 13 

// プレーヤー定数
#define PLAYER_SPEED 6
#define PLAYER_DAMAGE_FLY_X 5
#define PLAYER_DAMAGE_FLY_Y -25
#define PLAYER_MAX_LIFE 6
#define CHARGE_MAX 3
// プレーヤーのサイズ(DrawRotaGraphでの描画のためx,yが画像の中心座標であることに注意する)
#define PLAYER_W 32
#define PLAYER_H 32

// エネミー定数
#define ENEMY_SPEED 2
#define ENEMY_LIFE 2
#define ENEMY_enemyNum 10
#define ENEMY_FLY 8
#define ENEMY_HARPY_FLY 3
// ボス定数
#define BOSS_SPEED 50
#define ENEMY_BOSS_W 256
#define ENEMY_BOSS_H 256
#define BOSS_LASER_W 192
#define BOSS_LASER_H 192
// エネミーも同じくDrawRota描画に基づいたサイズ定数にする
#define ENEMY_W 32
#define ENEMY_H 32

// アイテム定数
#define ITEM_W 64
#define ITEM_H 64

// ショット定数
#define SHOT_W 32
#define SHOT_H 3
#define SHOT 3
#define SHOT_SPEED 20
#define SHOT_ARC 1		// 弧を描くための上方向加速度
#define SHOT_INTERVAL 5
#define SHOT_REMAIN 15