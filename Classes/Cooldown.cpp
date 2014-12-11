#include "Cooldown.h"


Cooldown::Cooldown()
{
}

void Cooldown::init(float timeToSet){
	time = timeToSet;
	timeRemaining = time;
	active = true;
	next = nullptr;
}

bool Cooldown::isActive(){
	return active;
}

bool Cooldown::isCompleted(){
	return (timeRemaining <= 0)? true : false;
}

void Cooldown::activate(){
	active = true;
}

void Cooldown::deactivate(){
	active = false;
}

void Cooldown::decreaseTime(float timeElapsed){
	timeRemaining -= timeElapsed;
	if(timeRemaining < 0.0f)
		timeRemaining = 0.0f;
}

void Cooldown::setNext(Cooldown *cooldown){
	next = cooldown;
}

Cooldown *Cooldown::getNext(){
	return next;
}

float Cooldown::getRelativeTime(){
	return timeRemaining/time;
}
