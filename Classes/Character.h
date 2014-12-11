#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Cooldown.h"
#include "Spell.h"

class Character
{
public:
	Character();
protected:
	float damages  [6];
	float defenses [6];
	int hp_max;
	int hp_current;
	Cooldown *_cooldown;
	int *spells [10];
};

#endif