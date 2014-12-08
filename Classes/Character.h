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
	int mana_max;
	int hp_current;
	int mana_current;
	Cooldown _playerCooldown;
	Spell *spells [10];
};

