#pragma once
//#include "Spell.h"

class Cooldown
{
public:
	Cooldown();
	bool isActive();
	bool isCompleted();
	void activate();
	void deactivate();
	void init(float);
	void decreaseTime(float);
	void setNext(Cooldown *);
	float getRelativeTime();
	Cooldown *getNext();
private:
	float timeRemaining;
	float time;
	bool active;
	Cooldown *next;
};

