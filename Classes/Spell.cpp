#include "Spell.h"


Spell::Spell()
{
}

void Spell::init(){
	index = -1;
	manaCost = 10;
	time = 3.0;
	for(int i = 0; i < 6; i++)
		elementalPower[i] = 0;
}

void Spell::setName(char *str){
	name = str;
}

void Spell::setDescription(char *str){
	description = str;
}

void Spell::setManaCost(int mana){
	manaCost = mana;
}

void Spell::setTime(float timeToSet){
	time = timeToSet;
}

void Spell::startCooldown(){
	cooldown.init(time);
}

void Spell::setIndex(int i){
	index = i;
}

void Spell::setElementalPower(int type, int value){
	elementalPower[type] = value;
}

bool Spell::isOnCooldown(){
	return !cooldown.isCompleted();
}

char *Spell::getName(){
	return name;
}

char *Spell::getDescription(){
	return description;
}

int Spell::getManaCost(){
	return manaCost;
}

int Spell::getElementalPower(int element){
	return elementalPower[element];
}

float Spell::getTime(){
	return time;
}

float Spell::getRelativePositionX(){
	return _positionX - ( 1 - _positionX);
}
