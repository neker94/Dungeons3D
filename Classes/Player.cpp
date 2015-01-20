#include "Player.h"

Player::Player()
{
	posX = 3;
	posY = 4;

	direction = Direction::NORTH;
	_cooldown = new Cooldown();
	_cooldown->init(3.0f);
	_cooldown->deactivate();

	level = 1;
	expPoints = 0;
	availablePoints = 0;
	setHpMax(200);
	setHpCurrent(getHpMax());
	
	for (int i = 0; i < 6; i++)
	{
		setDamages(i, 10);
		setDefenses(i, 10);
	}
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
	if(hp_current > hp_max)
		hp_current = hp_max;
}

float Player::getRelativeHP(){
	return (float)getHp()/(float)getHpMax();
}

void Player::setDamages(int index, float dmg){
	damages[index] = dmg;
}

void Player::setDefenses(int index, float def){
	defenses[index] = def;
}

void Player::setHpMax(int hp){
	hp_max = hp;
}

Cooldown *Player::getCooldown(){return _cooldown;}
int Player::getHp(){return hp_current;}
int Player::getHpMax(){return hp_max;}

void Player::doDamage(int index, float* damagePoints){
	Spell *spell = Atlas_Spell::createSpell(index);
	for(int i = 0; i < 6; i++){
		damagePoints[i] = damages[i]*spell->getElementalPower(i);
	}
	getCooldown()->init(spell->getTime());
}

void Player::takeDamage(float *damagePoints){
	float total = 0.0f;
	for(int i = 0; i < 6; i++){
		total += damagePoints[i]/defenses[i];
	}
	hp_current -= (int)total;
}

bool Player::doesLevelUp(){
	return (expPoints >= (level*level*level)+10); //n3+10
}

void Player::levelUp(){
	hp_max+=10;
	availablePoints += 5;
	level++;
	switch(level){
	case 2: spells.push_back(2); break;
	}
}

void Player::addDamagePoint(int i){
	if(availablePoints > 0){
		damages[i] += 1.0f;
		availablePoints--;
	}
}

void Player::addDefensePoint(int i){
	if(availablePoints > 0){
		defenses[i] += 1.0f;
		availablePoints--;
	}
}

float Player::getDamages(int i){
	return damages[i];
}

float Player::getDefenses(int i){
	return defenses[i];
}

int Player::getExperience(){
	return expPoints;
}


void Player::setExperience(int expe){
	expPoints = expe;
}

int Player::expUntilNLvl(){
	return (level*level*level)+10 - expPoints;
}

void Player::setLevel(int l){
	level = l;
}

int Player::getLevel(){
	return level;
}