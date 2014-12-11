#include "Enemy.h"


Enemy::Enemy()
{
}

void Enemy::performAction(){
	
	/* HERE IS THE CODE FOR IMPLEMENT IA
	as we can't make a hard sofisticated IA, we will asign a number to
	each action the enemy can perform. The greater this number is, the
	more chances to be performed the action will have.
	*/	
}

float *Enemy::doDamage(int index){
	Spell *spell = Atlas_Spell::createSpell(index);
	float damagePoints [6];
	for(int i = 0; i < 6; i++){
		damagePoints[i] = damages[i]*spell->getElementalPower(i);
	}
	getCooldown()->init(spell->getTime());
	return damagePoints;
}

void Enemy::takeDamage(float *damagePoints){
	float total = 0.0f;
	for(int i = 0; i < 6; i++){
		total += damagePoints[i]*defenses[i];
	}
	hp_current -= (int)total;
}

void Enemy::setCooldown(Cooldown *c){
	_cooldown = c;
}

void Enemy::setHpCurrent(int hp){
	hp_current = hp;
	if(hp_current < 0)
		hp_current = 0;
}

void Enemy::setDamages(float *dmg){
	for(int i = 0; i < sizeof(&dmg); i++){
		damages[i] = dmg[i];
	}
}

void Enemy::setDefenses(float *dfs){
	for(int i = 0; i < sizeof(&dfs); i++){
		defenses[i] = dfs[i];
	}
}

void Enemy::setHpMax(int hp){
	hp_max = hp;
}

Cooldown *Enemy::getCooldown(){return _cooldown;}
int Enemy::getHp(){return hp_current;}
int Enemy::getHpMax(){return hp_max;}

