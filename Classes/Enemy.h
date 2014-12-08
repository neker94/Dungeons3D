#include "Character.h"
#include "Spell.h"

class Enemy:Character
{
public:
	Enemy();
	static const int FIGHTER = 0;
	static const int CASTER = 1;
	static const int SILLY = 0;
	static const int SMART = 1;
	static const int CLEVER = 2;
	static const int SUPERCLEVER = 3;
	void performAction();
	void setTypeOfEnemy(int);
	void setKindoOfAction(int);
	void setDamages(float *);
	void setDefenses(float *);
	void setHpMax(int);
	void setHpCurrent(int);
	void setManaMax(int);
	void setManaCurrent(int);
	void setCooldown(Cooldown);
private:
	int typeOfEnemy;
	int kindOfActions;
	Spell *spells [10];
};

