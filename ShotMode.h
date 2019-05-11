#pragma once
#include "Common.h"

class ShotMode
{
public:

	int selectMode;			// 射撃モード選択( 0:通常射撃	1:三本射撃	3:貫通射撃 )

	void Select();
};