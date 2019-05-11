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

		// �v���[���[�����ȏ�߂Â����瓮���o��
		if ((x - player->x) < 1000)
		{
			state = STATE_MOVE;
		}
	}
	// �ړ����
	if (state == STATE_MOVE)
	{
		laserFlg = false;
		// �ړ��̉񐔂𐧌䂷��J�E���^�[����
		moveCount++;

		// �i�s�����ύX
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

		// �O���ɐi�ގ�
		if (moveDirection == false && moveCount % 50 == 0)
		{
			x += BOSS_SPEED;
			// ���ʉ�
			PlaySoundMem(footstepSound, DX_PLAYTYPE_BACK);
		}
		// ����ɐi�ގ�
		if (moveDirection == true && moveCount % 50 == 0)
		{
			x -= BOSS_SPEED;
			PlaySoundMem(footstepSound, DX_PLAYTYPE_BACK);
		}

		tagEffY = 950;

		// �J�E���g�����ȏ�ɂȂ�����^�[�Q�b�g��Ԃֈڍs
		if (moveCount >= 300)
		{

			state = STATE_TARGET;
		}
	}

	if (state == STATE_TARGET)
	{
		// �^�[�Q�b�g�t���O���I�t�̎�(�ŏ��̈��̂�)�A���ݎ������^�C�}�[�ɋL�^
		if (targetFlg == false)
		{
			moveCount = 0;
			targetTimer = GetNowCount();
			// ������
			changeDirection = false;

			targetFlg = true;
		}

		// �^�[�Q�b�g��Ԃɓ��������_���牽�b�o���������J�E���g�ɑ��
		targetCount = (GetNowCount() - targetTimer) / 1000;

		tagEffX = player->x;

		// ���ʉ��Đ�
		if (!CheckSoundMem(chargeSound))
		{
			PlaySoundMem(chargeSound, DX_PLAYTYPE_BACK);
		}


		// 5�b�o�ߌ�A�A�^�b�N�X�e�[�g�ֈڍs
		if (targetCount == 5)
		{
			targetFlg = false;
			state = STATE_ATTACK;
		}
	}

	if (state == STATE_ATTACK)
	{
		// �A�^�b�N��Ԃɓ������Ƃ�
		if (flashFlg == false && laserFlg == false)
		{
			flashFlg = true;
		}

		// �t���b�V���t���O����������
		if (flashFlg == true)
		{
			flashCounter++;
			// ���ʉ�
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
	
	// ��ɓ���������
	if (hitBody)
	{
		// ���ʉ�
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

	// �{�X�`�惁�C��
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
	// �^�[�Q�b�g���ǔ��G�t�F�N�g�`��
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
