#include "Player.h"

Player::Player()
{
	posX = 3;
	posY = 4;
	direction = Direction::NORTH;
	_cooldown = new Cooldown();
	_cooldown->init(3.0f);
	_cooldown->deactivate();
}

int Player::getX(){
	return posX;
}

int Player::getY(){
	return posY;
}

void Player::rotateLeft(){
	if(direction == Direction::NORTH)
		direction = Direction::WEST;
	else if(direction == Direction::WEST)
		direction = Direction::SOUTH;
	else if(direction == Direction::SOUTH)
		direction = Direction::EAST;
	else if(direction == Direction::EAST)
		direction = Direction::NORTH;
}

void Player::rotateRight(){
	rotateLeft();
	rotateLeft();
	rotateLeft();
}

void Player::move(){
	switch(direction){
	case Direction::NORTH:
		posY--;
		break;
	case Direction::WEST:
		posX--;
		break;
	case Direction::SOUTH:
		posY++;
		break;
	case Direction::EAST:
		posX++;
		break;
	}
}

int Player::getDirection(){
	return direction;
}

void Player::setDirection(int dir){
	direction = dir;
}

void Player::setCooldown(Cooldown *c){
	_cooldown = c;
}

void Player::setHpCurrent(int hp){
	hp_current = hp;
	if(hp_current < 0)
		hp_current = 0;
}

void Player::setDamages(float *dmg){
	for(int i = 0; i < sizeof(&dmg); i++){
		damages[i] = dmg[i];
	}
}

void Player::setDefenses(float *dfs){
	for(int i = 0; i < sizeof(&dfs); i++){
		defenses[i] = dfs[i];
	}
}

void Player::setHpMax(int hp){
	hp_max = hp;
}

Cooldown *Player::getCooldown(){return _cooldown;}
int Player::getHp(){return hp_current;}
int Player::getHpMax(){return hp_max;}

float *Player::doDamage(int index){
	Spell *spell = Atlas_Spell::createSpell(index);
	float damagePoints [6] = {0,0,0,0,0,0};
	for(int i = 0; i < 6; i++){
		damagePoints[i] = damages[i]*spell->getElementalPower(i);
	}
	getCooldown()->init(spell->getTime());
	return damagePoints;
}

void Player::takeDamage(float *damagePoints){
	float total = 0.0f;
	for(int i = 0; i < 6; i++){
		total += damagePoints[i]*defenses[i];
	}
	hp_current -= (int)total;
}