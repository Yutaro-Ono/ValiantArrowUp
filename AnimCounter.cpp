#include "AnimCounter.h"

void Anim::InitCount()
{
	itemCounter = 0;
    itemBaCounter = 0;
}

void Anim::TimeCounter()
{
	timer = GetNowCount();
	counter = (timer / 120) % 6;
}

void Anim::ItemCounter()
{
	itemCounter++;
    itemBaCounter++;

	if (itemCounter == 40)
	{
		itemCounter = 0;
	}

    if (itemBaCounter == 45)
    {
        itemBaCounter = 0;
    }
}
