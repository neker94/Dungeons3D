#include "Character.h"
#include "Spell.h"
#include "Atlas_Spell.h"

class Enemy:Character
{
public:
	Enemy();
	void performAction();
	void setDamages(float *);
	void setDefenses(float *);
	void setHpMax(int);
	void setHpCurrent(int);
	void setCooldown(Cooldown *);
	void takeDamage(float *);
	int getHp();
	int getHpMax();
	float *doDamage(int);
	Cooldown *getCooldown();
private:
	
};
