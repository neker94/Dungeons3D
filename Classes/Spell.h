#pragma once
#include "Cooldown.h"

class Spell
{
public:
	Spell();
	static const int PHYSIC = 0;
	static const int MAGIC = 1;
	static const int FIRE = 2;
	static const int ICE = 3;
	static const int LIGTH = 4;
	static const int DARKNESS = 5;
	void init();
	void setElementalPower(int, int);
	void setName(char*);
	void setDescription(char*);
	void setManaCost(int);
	void setTime(float);
	void startCooldown();
	void setIndex(int);
	bool isOnCooldown();
	char *getName();
	char *getDescription();
	int getManaCost();
	int getElementalPower(int);
	float getRelativePositionX();
	float getCooldownScaleImageWidth();
private:
	int elementalPower[6];
	int index;
	int manaCost;
	char *name;
	char *description;
	double time;
	float _positionX;
	float _postionY;
	Cooldown cooldown;
};

