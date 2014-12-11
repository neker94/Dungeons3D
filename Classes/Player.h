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
	void setDamages(float *);
	void setDefenses(float *);
	void setHpMax(int);
	void setHpCurrent(int);
	void setCooldown(Cooldown *);
	void takeDamage(float *);
	float *doDamage(int);
	int getHp();
	int getHpMax();
	Cooldown *getCooldown();
private:
	int posX;
	int posY;
	int direction;
};

#endif