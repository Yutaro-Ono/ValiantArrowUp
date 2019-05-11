#include "Item.h"

void Item::InitItem(int i)
{
    // iが5より下の場合回復アイテムとして登録
	if (i < 5)
	{
		type = TYPE_CURE;
		LoadDivGraph("data/textures/Item/Cure/CURE_ITEM.png", 5, 5, 1, 64, 64, cureItem);
        LoadDivGraph("Data/Textures/Item/Cure/CURE_EFFECT.png", 6, 3, 2, 64, 64, cureEffect);
		cureSound = LoadSoundMem("Data/Sound/SE/Item/AID_GET.mp3");
	}

    // iが5以上の場合スコアアイテムとして登録
	if (i >= 5)
	{
		type = TYPE_SCORE;
		LoadDivGraph("data/textures/Item/Score/SCORE_ITEM.png", 5, 5, 1, 64, 64, scoreItem);
		explSound = LoadSoundMem("Data/Sound/SE/Item/EXPLOSION_BALL.mp3");
	}

	posX = 0.0f;
	posY = 0.0f;
	visibleFlg = false;
    hitEffect = false;
	hitFlg = false;

	animTimer = 0;
	animCounter = 0;

}

void Item::SetPos(int i)
{
	if (i == 0)
	{
		posX = 2880.0f;
		posY = 890.0f;
	}
	if (i == 1)
	{
        posX = 7200.0f;
        posY = 192.0f;
	}
	if (i == 2)
	{
        posX = 8704.0f;
        posY = 640.0f;
	}
	if (i == 3)
	{
        posX = 13632.0f;
        posY = 384.0f;
	}
	if (i == 4)
	{
        posX = 16000.0f;
        posY = 704.0f;
	}
	if (i == 5)
	{
        posX = 2688.0f;
        posY = 640.0f;
	}
	if (i == 6)
	{
        posX = 4224.0f;
        posY = 890.0f;
	}
	if (i == 7)
	{
        posX = 7104.0f;
        posY = 890.0f;
	}
	if (i == 8)
	{
        posX = 7424.0f;
        posY = 192.0f;
	}
	if (i == 9)
	{
        posX = 9792.0f;
        posY = 192.0f;
	}
	if (i == 10)
	{
        posX = 9728.0f;
        posY = 704.0f;
	}
	if (i == 11)
	{
        posX = 11136.0f;
        posY = 448.0f;
	}
	if (i == 12)
	{
        posX = 10880.0f;
        posY = 890.0f;
	}
	if (i == 13)
	{
        posX = 13376.0f;
        posY = 384.0f;
	}
	if (i == 14)
	{
        posX = 192.0f;
        posY = 890.0f;
	}

}

void Item::hitPlayer(Player * player)
{
	
}


void Item::hitArrow(UI * ui)
{
	if (hitFlg == true && type == TYPE_SCORE)
	{
        // スコア加算
        ui->AddScore(0);

		// SE再生
		PlaySoundMem(explSound, DX_PLAYTYPE_BACK);

		visibleFlg = true;
        hitEffect = true;

		hitFlg = false;
	}
}

// プレーヤーに当たった時、回復して消滅
void Item::CurePlayer(Player * player)
{
	// プレーヤーの体力を回復し、消す(回復アイテムかどうかはCollisionActorで処理)
	if (visibleFlg == false && hitFlg == true && type == TYPE_CURE)
	{
        // プレーヤーの最大体力を超えていなければ体力回復
		if (!(player->hp >= PLAYER_MAX_LIFE))
		{
			player->hp += 1;
		}

        hitEffect = true;

		PlaySoundMem(cureSound, DX_PLAYTYPE_BACK);

		visibleFlg = true;
	}
}

void Item::DrawItem(Anim * anim, Camera * camera)
{
    if (visibleFlg == false)
    {
        if (type == TYPE_CURE)
        {
            DrawGraph(camera->GetScreenX(posX), camera->GetScreenY(posY), cureItem[anim->itemCounter / 10], TRUE);
            DrawGraph(camera->GetScreenX(posX), camera->GetScreenY(posY), cureEffect[3 + anim->itemBaCounter / 15], TRUE);
        }

        if (type == TYPE_SCORE && hitEffect == false)
        {
            DrawGraph(camera->GetScreenX(posX), camera->GetScreenY(posY), scoreItem[anim->itemBaCounter / 15], TRUE);
        }
    }


}

void Item::DrawEffect(Anim * anim, Camera * camera, Player * player)
{
	if(hitEffect == true && type == TYPE_SCORE)
	{
		animCounter++;


		if (anim->counter % 2)
		{
			DrawGraph(camera->GetScreenX(posX), camera->GetScreenY(posY), scoreItem[3], TRUE);
		}


		if (animCounter >= 60)
		{
			hitEffect = false;
		}
	}
	//else
	//{
	//	animCounter = 0;
	//}

	if (hitEffect == true && type == TYPE_CURE)
	{
		animCounter++;
		DrawGraph(camera->GetScreenX(player->x - PLAYER_W), camera->GetScreenY(player->y - PLAYER_H), cureEffect[3 + anim->itemBaCounter / 15], TRUE);

		if (animCounter >= 60)
		{
			hitEffect = false;
		}

	}
}
