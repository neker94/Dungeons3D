#include "Character.h"
#include "Spell.h"
#include "Atlas_Spell.h"

class Enemy:Character
{
public:
	Enemy();
	void performAction();
	void setDamages(int index, float dmg);
	void setDefenses(int index, float def);
	void setHpMax(int);
	void setHpCurrent(int);
	float getRelativeHP();
	void setCooldown(Cooldown *);
	void takeDamage(float *);
	int getHp();
	int getHpMax();
	float *doDamage(int);
	Cooldown *getCooldown();



	const char *spriteName;
private:
	
};
