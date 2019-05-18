#include "Common.h"

Scene scene;
Camera camera;
Collision coll;
CollisionActor collA;
Player player;
Boss boss;
Legion legion;
Bg bg;
Effect effect;
Sound sound;
UI ui;
Map map;
Anim anim;
Debug debug;

// 配列用定数
const int shotNum = 5;
const int enemyAllNum = 24;
const int itemAllNum = 15;
const int scoreItemNum = 10;

Shot shot[shotNum];
Enemy enemy[enemyAllNum];
Item item[itemAllNum];

//-------------------------------------------------------------------------------------------------//
//										WinMain関数
//------------------------------------------------------------------------------------------------//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	// 画面モードの設定
	SetGraphMode(SCREEN_W, SCREEN_H, 16);
	ChangeWindowMode(TRUE);
	// DXライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);			// 描画先を裏画面に設定
	
	// フォントをロード
	ui.LoadFont();
	//text.setFontImage(16, 6, "data/Fonts/font.bmp");
	SetFontSize(110);

	// エネミー画像をロード
	legion.GetImage("data/textures/actors/enemies/Enemy_Moff.png", "data/textures/actors/enemies/Enemy_Harpy.png");

	debug.Init();

	//------------------------------------//
	// ゲームループ
	//-----------------------------------//
	while (debug.flg)
	{
		ClearDrawScreen();

		if (scene.manager == scene.STATE_INIT)
		{
			// 初期化
			debug.Init();
			anim.InitCount();
			camera.Init();
			player.Init();
			bg.Init();
			effect.Init();
			sound.Init();
			ui.Init();
			map.Init();
			map.Create();
			scene.Init();
			boss.Init();

			// 配列初期化
			for (int i = 0; i < enemyAllNum; i++)
			{
				enemy[i].Init();
				legion.SetPos(&enemy[i], i);
				if (i < shotNum)
				{
					shot[i].Init(&player);
				}
				if (i < itemAllNum)
				{
					item[i].InitItem(i);
					item[i].SetPos(i);
				}
			}

			scene.manager = scene.STATE_TITLE;
		}

		// 音楽コントロール
		sound.MusicControl(&scene, &boss);

		// タイトルシーン処理
		if (scene.manager == scene.STATE_TITLE)
		{
			ui.titleDraw();
		}

		//　チュートリアルシーン
		if (scene.manager == scene.STATE_TUTORIAL)
		{
			// デバッグ用表示
			DrawString(SCREEN_W / 2, SCREEN_H / 2, "ちゆーとりある", GetColor(255, 255, 255));
		}
		
		// イントロシーン
		if (scene.manager == scene.STATE_INTRO)
		{
			// デバッグ用表示
			DrawString(SCREEN_W / 2, SCREEN_H / 2, "イントロ", GetColor(255, 255, 255));
		}

		if (scene.manager == scene.STATE_GAME)
		{
			//--------------------------------//
			// Update関数群
			//-------------------------------//
			{
				bg.Update(&camera);
				// アニメーションタイマー更新
				anim.TimeCounter();
				anim.ItemCounter();
				camera.MovePosCam(&player);

				// プレーヤー関連処理
				player.CheckHitBlockLeft(&map, &camera, &coll);
				player.CheckHitBlockRight(&map, &camera, &coll);
				player.CheckHitBlockTop(&map, &coll, &camera);
				player.CheckHitBlockUnder(&map, &camera, &coll);
				player.GravityProcess();

				player.Control();

				for (int i = 0; i < shotNum; i++)
				{
					shot[i].Update(&player);	// ショットの座標をターゲティング
                    shot[i].EraseOut(&camera, &player);
					if (shot[i].shotFlg == false)
					{
						player.ShotProcess(&camera, &anim, &shot[i], &effect);	// 飛ぶ
					}
				}
				collA.HitBoss(&player, &boss);
				collA.HitBossLaser(&boss, &player);
				player.MoveRightPlayer();
				player.MoveLeftPlayer();
				player.JumpPlayer();
				player.Damage();

				// エネミー関連処理
				for (int i = 0; i < enemyAllNum; i++)
				{
					enemy[i].HitBlockVoid(&coll, &map);
					enemy[i].HitBlockTop(&camera, &coll, &map);
					enemy[i].HitBlockUnder(&camera, &coll, &map);
					enemy[i].HitBlockRight(&camera, &coll, &map, &player);
					enemy[i].HitBlockLeft(&camera, &coll, &map, &player);
					enemy[i].MoveRoutine(i);
					enemy[i].DamageReaction(&player, i);
					enemy[i].TrackRoutine(&player);
					enemy[i].Gravity(i);

					enemy[i].Died(&ui);

				}

				//----------------------------------------------------//
				// アイテム関連
				//---------------------------------------------------//
				for (int i = 0; i < itemAllNum; i++)
				{
					collA.HitItem(&player, &item[i]);

					item[i].hitArrow(&ui);
					item[i].CurePlayer(&player);
				}

				boss.Routine(&player);
				boss.HitShotBody();

				for (int i = 0; i < shotNum; i++)
				{
					shot[i].FlyUpdate(&player);
					shot[i].HitBlock(&map, &coll, &player);
					effect.Targeting(&player, &shot[i]);
					collA.HitBossShot(&boss, &shot[i]);
					for (int j = 0; j < enemyAllNum; j++)
					{
						collA.HitEtoP(&player, &enemy[j]);
						collA.HitEnemShot(&enemy[j], &shot[i]);
						shot[i].HitEnemy(&camera, &anim, &enemy[j], &effect);
					}
					for (int j = 0; j < itemAllNum; j++)
					{
						collA.HitShotItem(&shot[i], &item[j]);
					}
				}

				debug.Tyousa(&player, &enemy[1], &item[14], &boss, &map, &camera, &shot[0], &effect);
			}
			//--------------------------------//
			// Draw関数群
			//-------------------------------//
			{
				bg.DrawBack(&camera, &player);
				map.Draw(&camera, &player);
				// エネミー描画
				for (int i = 0; i < enemyAllNum; i++)
				{
					legion.Draw(&enemy[i], &anim, &camera, i);
					enemy[i].Draw(&camera, &anim, &ui);
				}
				// ボスエネミー関連の描画
				boss.Draw(&anim, &camera);
				boss.DrawEffect(&anim, &camera);
				// ショットの描画
				for (int i = 0; i < shotNum; i++)
				{
					shot[i].Draw(&camera, &player);
					shot[i].DrawHitEffect(&camera);
					player.Draw(&camera, &shot[i], &anim);
				}
				// アイテム関連の描画
				for (int i = 0; i < itemAllNum; i++)
				{
					item[i].DrawItem(&anim, &camera);
                    item[i].DrawEffect(&anim, &camera, &player);
				}
				// エフェクト描画
				effect.ShotHitDraw(&camera, &anim);
				effect.ShotCharge1(&camera, &player, &anim);
				effect.ShotCharge2(&camera, &player, &anim);

				bg.DrawFront(&camera, &player);
				// HUD
				ui.DrawHUD();
				ui.DrawLifebox(&player);
				ui.DrawHUDframe();
				ui.DrawScore();
				ui.SprayBlood(&player);
			}
		}

		if (scene.manager == scene.STATE_CLEAR)
		{
			ui.GameClear();
		}

		if (scene.manager == scene.STATE_GAMEOVER)
		{
			ui.GameOver();
		}

		if (scene.manager == scene.STATE_ENDGAME)
		{
			break;
		}

		// シーン遷移の操作用関数
		scene.Control(&player, &boss, &ui);

		// Debug関数
		debug.Escape();

		ScreenFlip();						// 裏画面を表画面に反映
	}

	DxLib_End();

	return 0;
}