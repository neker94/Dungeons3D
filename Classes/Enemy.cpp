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

void Enemy::setCooldown(Cooldown c){
	_playerCooldown = c;
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

void Enemy::setKindoOfAction(int kind){
	kindOfActions = kind;
}

void Enemy::setManaCurrent(int mana){
	mana_current = mana;
}

void Enemy::setManaMax(int mana){
	mana_max = mana;
}