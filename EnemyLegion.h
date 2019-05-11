#pragma once
#include "Common.h"

class Enemy;

class Legion
{
	public:

	const int enemyNum = 15;

	// �G�l�~�[�̉摜���擾����֐�
	void GetImage(const char* imgFileName, const char* fileNameHarpy);

	// �G�l�~�[��Position���Z�b�g����֐�
	void SetPos(Enemy *enemy, int i);

	// �G�l�~�[�̕`��
	void Draw(Enemy * enemy, Anim * anim, Camera * camera, int i);
};