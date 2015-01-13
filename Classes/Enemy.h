#include "Character.h"
#include "Spell.h"
#include "Atlas_Spell.h"

class Enemy:Character
{
public:
	Enemy();
	int performAction();
	void setDamages(int index, float dmg);
	void setDefenses(int index, float def);
	void setHpMax(int);
	void setHpCurrent(int);
	float getRelativeHP();
	void setCooldown(Cooldown *);
	void takeDamage(float *);
	int getHp();
	int getHpMax();
	void doDamage(int, float*);
	void addSpell(int);
	Cooldown *getCooldown();
	const char *spriteName;
	int exp;
};
