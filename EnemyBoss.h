#pragma once
#include "Common.h"

class Anim;
class Camera;
class Map;
class Collision;
class Player;

class Boss
{
	public:

	int graph[6];
	int standGraph;

	// �{�X�̏�Ԃ��i�[
	int state;

	// ���W
	float x;
	float y;
	// �̗�
	int hp;
	// �����t���O
	bool dir;
	// �����Ă��邩���Ȃ����̃t���O
	bool moveFlg;
	// �O�Ɉړ����邩���Ɉړ����邩�̃t���O(STATE_MOVE���Ɏg�p)
	bool moveDirection;
	bool changeDirection;
	// ���S�t���O
	bool dieFlg;
	// �ړ�����^�[�Q�b�g��ԂɈڂ�܂ł̃J�E���g
	int moveCount;

	// �{�X�̃{�f�B�Ƀq�b�g
	bool hitBody;
	int hitCount;
	// �{�X�̎�_�Ƀq�b�g
	bool hitWeak;

	// �^�[�Q�b�g���(��:�^�[�Q�b�g��Ԃɓ��������̌��ݎ������i�[�A��:)
	int targetTimer;
	int targetCount;
	bool targetFlg;

	// �^�[�Q�b�g���̑����G�t�F�N�g�֘A
	float tagEffX;
	float tagEffY;

	// ���[�U�[���ˊ֘A
	bool flashFlg;
	bool laserFlg;
	int flashCounter;
	int laserTimer;
	int laserCount;

	// �G�t�F�N�g�֘A
	int shieldEffect[10];
	int tagEff[6];
	int tagChargeEff[8];
	int laserFlash[6];
	int laserGraph[6];

	// ���ʉ�
	int chargeSound;
	int flashSound;
	int laserSound;
	int footstepSound;
	int shieldSound;

	// �A�j���[�V�����p�J�E���^�[
	int animCounter;



	enum State
	{
		STATE_FREEZE,
		STATE_MOVE,
		STATE_TARGET,
		STATE_ATTACK,
		STATE_RAGE,
		STATE_DEATH
	};



	void Init();
	void Routine(Player * player);
	void HitShotBody();
	void Damage();
	void Draw(Anim * anim, Camera * camera);
	void DrawEffect(Anim * anim, Camera * camera);
};