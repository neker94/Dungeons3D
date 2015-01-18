#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Direction.h"
#include "Character.h"
#include "Spell.h"
#include "Atlas_Spell.h"

class Player:Character
{
public:
	Player();
	void move();
	void rotateLeft();
	void rotateRight();
	int getX();
	int getY();
	int getDirection();
	void setDirection(int);
	void setDamages(int index, float dmg);
	void setDefenses(int index, float def);
	float getDamages(int index);
	float getDefenses(int index);
	void setHpMax(int);
	void setHpCurrent(int);
	float getRelativeHP();
	void addDamagePoint(int i);
	void addDefensePoint(int i);
	void setCooldown(Cooldown *);
	void takeDamage(float *);
	void doDamage(int, float*);
	int getHp();
	int getHpMax();
	Cooldown *getCooldown();
	bool doesLevelUp();
	void levelUp();
	int availablePoints;
private:
	int posX;
	int posY;
	int direction;
	int expPoints;
	int level;
};

#endif