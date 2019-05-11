#pragma once
#include "Common.h"
class Player;
class Anim;
class Shot;


class Item
{
public:

	// ���W
	float posX;
	float posY;

	// �A�C�e���̎��
	enum Type
	{
		TYPE_CURE,
		TYPE_SCORE
	};
	// ��ފi�[�p
	int type;


	// �񕜃A�C�e��
	int cureItem[5];
	// �X�R�A�A�C�e��
	int scoreItem[5];

    // �G�t�F�N�g
    int cureEffect[6];
	int cureSound;

	int explSound;

	// �����Ă��邩���Ȃ����̃t���O
	bool visibleFlg;

    // ���Ŏ��̃G�t�F�N�g����
    bool hitEffect;
    
	// �v���[���[�ɓ����������ǂ���
	bool hitFlg;

	// �A�j���[�V�����p�^�C�}�[
	int animTimer;
	int animCounter;

	// �֐�
	void InitItem(int i);
	void SetPos(int i);
	void hitPlayer(Player * player);
	void hitArrow(UI * ui);
	void CurePlayer(Player * player);
	void DrawItem(Anim * anim, Camera * camera);
    void DrawEffect(Anim * anim, Camera * camera, Player * player);
};